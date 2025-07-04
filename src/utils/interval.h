#ifndef INTERVAL_H
#define INTERVAL_H

#include "../config.hpp"
// #include "color.h"
// #include "vec3.h"

class Interval {
  public:
    double min;
    double max;

    // Ctors
    Interval() : min(+infinity), max(-infinity) {} // Interval will be null
    Interval(double min, double max) : min(min), max(max) {}

    //
    double size() const { return max - min; }
    bool contains(double x) const { return min <= x && x <= max; } // [min, max]
    bool surrounds(double x) const { return min < x && x < max; }  // (min, max)
    double clamp(double x) const {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    static const Interval empty;    // Interval with no values in btween
    static const Interval universe; // Intervall with ALL possible values in btween
};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif
