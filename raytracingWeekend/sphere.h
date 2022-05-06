#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	sphere() = default;
	sphere(const point3& center, const double radius, shared_ptr<material> matPtr) : center(center), radius(radius), matPtr(matPtr) {};
	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;

public:
	point3 center;
	shared_ptr<material> matPtr;
	double radius;
};