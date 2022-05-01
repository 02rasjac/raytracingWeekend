#pragma once

#include "ray.h"

struct hitRecord {
	point3 p;
	vec3 normal;
	double t;
	bool frontFace;

	/*
	* Set the facenormal to always point *against* the hitting ray.
	* @param r The hitting ray.
	* @param outwardNormal The normal pointing outwards.
	*/
	inline void setFaceNormal(const ray& r, const vec3& outwardNormal) {
		frontFace = dot(r.direction(), outwardNormal) < 0; // Ray hits face from outside
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class hittable {
public:
	/*
	* Check collision between ray r and a hittable object.
	* @param r Ray to check collision with.
	* @param tMin Minimum value on parameter t.
	* @param tMax Maximum value on parameter t.
	* @param rec Record to save the collision in.
	* @return True if collided, otherwise false.
	*/
	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const = 0;
};