#pragma once

#include <cmath>
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

// Common Headers
#include "Ray.h"
#include "utils/color.h"
#include "utils/vec3.h"

namespace conf {

const uint32_t W_HEIGHT = 980; // Not used
const double ASPECT_RATIO = 16.0 / 9.0;
const uint32_t W_WIDTH = 600;

} // namespace conf

#define TIMER 1
