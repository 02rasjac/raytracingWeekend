#pragma once

#include "rtweekend.h"

class camera {
public:
	camera();
	ray getRay(double u, double v) const;
private:
	point3 origin;
	point3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};

