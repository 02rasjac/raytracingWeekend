#pragma once

#include "rtweekend.h"

class camera {
public:
	/*
	* @param vfov Vertical Field-of-View in degrees.
	* @param aspectRatio ratio between vertical and horizontal length (i.e 16:9 = 16/9)
	*/
	camera(point3 lookfrom, point3 lookat, vec3 vup, const double vfov, const double aspectRatio);
	ray getRay(double s, double t) const;
private:
	point3 origin;
	point3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};

