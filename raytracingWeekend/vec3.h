#pragma once

#include <cmath>
#include <iostream>
#include "rtweekend.h"

using std::sqrt;

class vec3 {
public:
	vec3(): e{0, 0, 0} {};
	vec3(double eAll) : e{ eAll, eAll, eAll } {};
	vec3(double e0, double e1, double e2): e{e0, e1, e2} {};
	double x() const { return e[0]; };
	double y() const { return e[1]; };
	double z() const { return e[2]; };
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); };
	double operator[](int i) const { return e[i]; };
	double& operator[](int i) { return e[i]; };

	vec3& operator+=(const vec3& v) {
		e[0] += v[0];
		e[1] += v[1];
		e[2] += v[2];
		return *this;
	}
	vec3& operator*=(const double d) {
		e[0] *= d;
		e[1] *= d;
		e[2] *= d;
	}
	vec3& operator/=(const double d) { return *this *= 1 / d; };
	double lengthSquare() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	};
	double length() const {
		return sqrt(lengthSquare());
	};
public:
	double e[3]; // Elements
};

// Type aliases for vec3
using point3 = vec3;
using color = vec3;

// =================
// Utility functions
// =================

// Outstream vectors
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const double d, const vec3& v) {
	return vec3(d * v.e[0], d * v.e[1], d * v.e[2]);
}

inline vec3 operator*(const vec3& v, const double d) {
	return d * v;
}

inline vec3 operator/(const vec3& v, const double d) {
	return (1 / d) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(
		u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]
	);
}

inline vec3 unitVector(const vec3& v) {
	return v / v.length();
}

inline vec3 random() {
	return vec3(randomDouble(), randomDouble(), randomDouble());
}

inline vec3 random(const double min, const double max) {
	return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

inline vec3 randomInUnitSphere() {
	while (true) {
		auto p = random(-1, 1);
		if (p.lengthSquare() >= 1) continue;
		return p;
	}
}