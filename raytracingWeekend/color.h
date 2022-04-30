#pragma once

#include <iostream>
#include "vec3.h"

/**
 * Writes the translated [0,255] value of each color-component.
 *
 * @param out Outstream which to write to.
 * @param pixelColor The color for the pixel as a vector.
*/
void writeColor(std::ostream& out, color pixelColor) {
	out << static_cast<int>(255.999 * pixelColor.x()) << ' '
		<< static_cast<int>(255.999 * pixelColor.y()) << ' '
		<< static_cast<int>(255.999 * pixelColor.z()) << '\n';
}