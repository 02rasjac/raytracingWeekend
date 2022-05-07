#pragma once

#include "rtweekend.h"
#include "hittable.h"

struct hitRecord;

class material {
public:
	virtual bool scatter(const ray& rayIn, const hitRecord& rec, color& atteunation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
	lambertian(const color& color) : albedo(color) {};
	virtual bool scatter(const ray& rayIn, const hitRecord& rec, color& atteunation, ray& scattered) const override;
public:
	color albedo;
};

class metal : public material {
public:
	metal(const color& color, const double fuzz) : albedo(color), fuzz(fuzz < 1 ? fuzz : 1) {};
	virtual bool scatter(const ray& rayIn, const hitRecord& rec, color& atteunation, ray& scattered) const override;
public:
	color albedo;
	double fuzz;
};

class dielectric : public material {
public:
	dielectric(const double indexOfRefraction) : indexOfRefraction(indexOfRefraction) {};
	virtual bool scatter(const ray& rayIn, const hitRecord& rec, color& atteunation, ray& scattered) const override;
private:
	static double reflectance(const double cosine, const double refIdx) {
		// Using Schlick's approximation
		auto r0 = (1.0 - refIdx) / (1.0 + refIdx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1.0 - cosine), 5);
	}
public:
	double indexOfRefraction;
};

