#pragma once

#include <memory>
#include <cmath>
#include <limits>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
static constexpr double infinity = std::numeric_limits<double>::infinity();
static constexpr double pi = 3.1415926535897932385;

// Utility functions
inline double degToRad(const double deg) {
	return (deg * pi) / 180.0;
}

// Common headers
#include "ray.h"
#include "vec3.h"