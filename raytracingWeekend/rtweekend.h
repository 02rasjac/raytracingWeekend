#pragma once

#include <memory>
#include <cmath>
#include <limits>
#include <cstdlib>

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

/*
* @return Random double number in [0, 1).
*/
inline double randomDouble() {
	return rand() / (RAND_MAX + 1.0);
}

/*
* Generates a random double in [min, max).
* @param min Minimum value.
* @param max Maximum value.
* @return Random double number in [min, max).
*/
inline double randomDouble(const double min, const double max) {
	return min + (max - min) * randomDouble();
}

/*
* Clamp the value of x to be in [min, max].
* @param x Value to be clamped.
* @param min Minimum value.
* @param max Maximum value.
* @return min if x < min, max if x > max, else x;
*/
inline double clamp(const double x, const double min, const double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

// Common headers
#include "ray.h"
#include "vec3.h"