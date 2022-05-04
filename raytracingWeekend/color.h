#pragma once

#include <iostream>
#include "vec3.h"

/**
 * Writes the translated [0,255] value of each color-component, including antialising.
 *
 * @param out Outstream which to write to.
 * @param pixelColor The color for the pixel as a vector.
 * @param samplesPerPixel Number of pixels to be included in antialising
*/
void writeColor(std::ostream& out, color pixelColor, const int samplesPerPixel) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	// Divide color by the sample
	auto scale = 1.0 / samplesPerPixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Write the color
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}