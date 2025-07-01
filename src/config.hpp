#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <stdint.h>

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }
inline double random_double() { return std::rand() / (RAND_MAX + 1.0); }                      // Rand real num [0:1) (never 1)
inline double random_double(double min, double max) { return (max - min) * random_double(); } // Rand real num [min:max]

// Common Headers
#include "Ray.h"
#include "utils/color.h"
#include "utils/interval.h"
#include "utils/vec3.h"

namespace conf {

const int W_HEIGHT = 980; // Not used
const double ASPECT_RATIO = 16.0 / 9.0;
const int W_WIDTH = 1920;

} // namespace conf
