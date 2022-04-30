#pragma once

#include "vec3.h"

class ray {
public:
	ray() = default;
	/**
	* @param origin Startingpoint on the line (t = 0).
	* @param direction Directionvector for the line.
	*/
	ray(const point3& origin, const vec3& direction) : ori(origin), dir(direction) {};
	point3 origin() const { return ori; };
	vec3 direction() const { return dir; };
	/**
	* @param t Parameter t in equation P(t) = <origin> + t * <direction>.
	* @return A point on the ray at t
	*/
	point3 at(const double t) { return ori + t * dir; };
private:
	point3 ori;
	vec3 dir;
};

