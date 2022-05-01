#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	sphere() = default;
	sphere(const point3& center, const double radius) : center(center), radius(radius) {};
	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec);

public:
	point3 center;
	double radius;
};