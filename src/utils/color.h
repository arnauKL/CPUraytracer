#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"
#include <iostream>

// Also shamelessly stolen from chapter 3.1:
// https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/colorutilityfunctions

using color = vec3; // A color is an alias for a vec3

void write_color(std::ostream &out, const color &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity = Interval(0.0, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
