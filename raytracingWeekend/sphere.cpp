#include "sphere.h"
#include <assert.h>

bool sphere::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
    vec3 oc = r.origin() - center; // Vector from origin to center
    auto a = r.direction().lengthSquare();
    auto halfB = dot(oc, r.direction());
    auto c = oc.lengthSquare() - radius * radius;
    auto discriminant = halfB * halfB - a * c;
    if (discriminant < 0)
        return false; // Did not hit the sphere

    auto sqrtd = sqrt(discriminant);

    // Check if the roots are within reach
    auto root = (-halfB - sqrtd) / a;
    if (tMin > root || root > tMax) {
        root = (-halfB + sqrtd) / a;
        if (tMin > root || root > tMax) {
            return false; // Did not hit spehere withing reach ([tMin, tMax])
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);

    assert(rec.normal.lengthSquare() == 1);
    return true;
}
