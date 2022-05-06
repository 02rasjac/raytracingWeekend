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
	metal(const color& color) : albedo(color) {};
	virtual bool scatter(const ray& rayIn, const hitRecord& rec, color& atteunation, ray& scattered) const override;
public:
	color albedo;
};

