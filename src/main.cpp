#include <iostream>

#include "config.hpp"
#include "hittable/Sphere.h"
#include "hittable/hittable.h"
#include "hittable/hittable_list.h"
#include "utils/vec3.h"

#include <chrono>
using namespace std::chrono; // To time execution

color ray_color(const Ray &r, const Hittable_list &world) {
    // The following values are those of an arbitrary sphere
    hit_record temp_rec;
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    // lerp bg
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {

    /// Image settings
    double aspect_ratio = conf::ASPECT_RATIO; // 16:9, used to find height
    int image_width = conf::W_WIDTH;
    int image_height = (image_width / aspect_ratio);      // Finding height
    image_height = (image_height < 1) ? 1 : image_height; // If less than 1, make it 1

    /// Camera settings
    // Camera -> eye point: point from where rays originate
    // The vector from the camera is orthogonal to the center
    // of the viewport (will have to fix the coords system of the image)
    // Distance from the camera to the viewport will be 1 (focal length)
    double focal_length = 1.0;
    // Viewport settings
    double viewport_height = 2.0f;
    double viewport_width = viewport_height * (double(image_width) / image_height);
    // This time the real aspect ratio is calculated, 16:9 is the ideal one but might
    // differ from the real one due to integer rounding an clamping at 1.

    // +x --> right
    // +y --> up
    // -z --> to the viewport
    point3 camera_center = point3(0, 0, 0); // Why not
    // We define +y as up. This conflicts with the way images are rendered, where +y = down
    // To mitigate this, scan from top-left to bottom right using vectors Vu (delta u) and Vv (delta v)
    // to jump btween points (pixels) in the viewport.

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);   // horizontal
    vec3 viewport_v = vec3(0, -viewport_height, 0); // vertical, negative bcs y axis is flipped

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel. (reminder: "-z" -> to the viewport, "-x" > left, "-y" -> down, but -(-y) -> up)
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    /// World settings
    Hittable_list world;                                            // Stores a list of objects present that can be hit
    world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5));    // Lil sphere
    world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100)); // Massive sphere to emulate a ground

    /// Render
    // Write loading info to the clog stream (the standard output stream is where the image gets printed)
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    auto start = high_resolution_clock::now();

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            // Pretty self explanatory
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction); // (origin, dir)

            /*// Generate the pixel based on coordinates of the image
            color pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.0);*/

            // Generate the pixel calculating the colour of the object hit by the ray
            color pixel_color = ray_color(r, world);

            // Write the colour to stdout
            write_color(std::cout, pixel_color);
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::clog << "\rDone in " << duration.count() / 1000.0 << " ms                        \n";

    // '\r' replaces characters

    return 0;
}
