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
    scattered = ray(rec.p, reflected + fuzz * randomInUnitSphere());
    atteunation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0.0); // Return TRUE if reflected, FALSE if absorbed
}

bool dielectric::scatter(const ray& rayIn, const hitRecord& rec, color& atteunation, ray& scattered) const {
    atteunation = color(1.0);
    auto refractionRatio = rec.frontFace ? (1.0 / indexOfRefraction) : indexOfRefraction;
    auto unitDirection = unitVector(rayIn.direction());
    auto refracted = refract(unitDirection, rec.normal, refractionRatio);
    scattered = ray(rec.p, refracted);
    return true;
}
