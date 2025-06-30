#include <iostream>

#include "Ray.h"
#include "utils/color.h"
#include "utils/vec3.h"

color ray_color(const Ray &r) {

    vec3 unit_direction = unit_vector(r.direction()); // scaled to unit length, so -1:1
    auto a = 0.5 * (unit_direction.y() + 1.0);        // Scales from -1:1 to 0:1
    // Lerp btween blue and white: blendValue = (1-a) * startValue + a * endValue
    return (1 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); // white and light blue
}

int main() {

    /// Image settings
    double aspect_ratio = 16.0 / 9.0; // 16:9, used to find height
    int image_width = 400;
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

    /// Render
    // Write loading info to the clog stream (the standard output stream is where the image gets printed)
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

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
            color pixel_color = ray_color(r);

            // Write the colour to stdout
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone!                        \n";

    // '\r' replaces characters

    return 0;
}
