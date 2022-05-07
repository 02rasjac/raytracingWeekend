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
    vec3 direction;
    auto unitDirection = unitVector(rayIn.direction());

    double cosTheta = fmin(dot(-rayIn.direction(), rec.normal), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    // Reflect or refract
    if (refractionRatio * sinTheta > 1.0 || reflectance(cosTheta, refractionRatio) > randomDouble()) // Must reflect
        direction = reflect(unitDirection, rec.normal);
    else // Can refract
        direction = refract(unitDirection, rec.normal, refractionRatio);
    scattered = ray(rec.p, direction);
    return true;
}
