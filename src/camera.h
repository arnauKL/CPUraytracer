#ifndef CAMERA_H
#define CAMERA_H

#include "config.hpp"
#include "hittable/hittable.h"

class Camera {
    // All variables will be public and set by default, modified when needed by the owning code
  public:
    double aspect_ratio = 1.0;
    int image_width = 100;

    void render(const hittable &world) {
        initialize();

        // PPM Header
        std::cout << "P3\n" << image_width << " " << _image_height << "\n255\n";

        // Rendering image to stdout
        for (int j = 0; j < _image_height; j++) {
            // Write loading info to the clog stream (the standard output stream is where the image gets printed)
            std::clog << "\rScanlines remaining: " << (_image_height - j) << ' ' << std::flush;

            for (int i = 0; i < image_width; i++) {

                // Pretty self explanatory
                auto pixel_center = _pixel00_loc + (i * _pixel_delta_u) + (j * _pixel_delta_v);
                auto ray_direction = pixel_center - _center;
                Ray r(_center, ray_direction); // (origin, dir)

                /*// Generate the pixel based on coordinates of the image
                color pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.0);*/

                // Generate the pixel calculating the colour of the object hit by the ray
                color pixel_color = ray_color(r, world);

                // Write the colour to stdout
                write_color(std::cout, pixel_color);
            }
        }
    }

  private:
    int _image_height;   // Rendered image height (calculated from aspect ratio and width)
    point3 _center;      // Camera center
    point3 _pixel00_loc; // Location of px 0,0
    vec3 _pixel_delta_u; // Espai fins al seg píxel a la dreta
    vec3 _pixel_delta_v; // Espai fins al següent píxel a sota

    void initialize() {
        // Function to initialize all variables (hard-coded)
        // Works kind of as a constructor

        // // Camera -> eye point: point from where rays originate
        // // The vector from the camera is orthogonal to the center
        // // of the viewport (will have to fix the coords system of the image)
        // // Distance from the camera to the viewport will be 1 (focal length)
        _image_height = int(image_width / aspect_ratio);
        _image_height = (_image_height < 1) ? 1 : _image_height;

        // Camera fixed at 0,0,0
        // // +x --> right
        // // +y --> up
        // // -z --> to the viewport
        _center = point3(0.0, 0.0, 0.0);
        // We define +y as up. This conflicts with the way images are rendered, where +y = down
        // To mitigate this, scan from top-left to bottom right using vectors Vu (delta u) and Vv (delta v)
        // to jump btween points (pixels) in the viewport.

        // Viewport dimensions
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width) / _image_height);
        // This time the real aspect ratio is calculated, 16:9 is the ideal one but might
        // differ from the real one due to integer rounding an clamping at 1.

        vec3 viewport_u = vec3(viewport_width, 0, 0);   // horizontal
        vec3 viewport_v = vec3(0, -viewport_height, 0); // vertical, negative bcs y axis is flipped

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        _pixel_delta_u = viewport_u / image_width;
        _pixel_delta_v = viewport_v / _image_height;

        // Calculate the location of the upper left pixel. (reminder: "-z" -> to the viewport, "-x" > left, "-y" -> down, but -(-y) -> up)
        auto viewport_upper_left = _center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        _pixel00_loc = viewport_upper_left + 0.5 * (_pixel_delta_u + _pixel_delta_v);
    }

    color ray_color(const Ray &r, const hittable &world) const {
        // Info of the hit
        hit_record rec;

        // If there is a hit from the ray btween 0 and inf, colour the object with the normal
        if (world.hit(r, Interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direction = unit_vector(r.direction());

        // lerp bg
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif // !CAMERA_H
