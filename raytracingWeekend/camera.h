#pragma once

#include "rtweekend.h"

class camera {
public:
	/*
	* @param vfov Vertical Field-of-View in degrees.
	* @param aspectRatio ratio between vertical and horizontal length (i.e 16:9 = 16/9)
	*/
	camera(const double vfov, const double aspectRatio);
	ray getRay(double u, double v) const;
private:
	point3 origin;
	point3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};

