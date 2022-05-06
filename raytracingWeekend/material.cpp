#include "material.h"

bool lambertian::scatter(const ray& rayIn, const hitRecord& rec, color& atteunation, ray& scattered) const
{
    auto scatterDirection = rec.normal + randomUnitVector();
    // Direction (0,0,0) causes problems
    if (scatterDirection.nearZero())
        scatterDirection = rec.normal;
    scattered = ray(rec.p, scatterDirection);
    atteunation = albedo;
    return true;
}

bool metal::scatter(const ray& rayIn, const hitRecord& rec, color& atteunation, ray& scattered) const {
    auto reflected = reflect(rayIn.direction(), rec.normal);
    scattered = ray(rec.p, reflected);
    atteunation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0.0); // Return TRUE if reflected, FALSE if absorbed
}
