#include "camera.h"

camera::camera(point3 lookfrom, point3 lookat, vec3 vup, const double vfov, const double aspectRatio) {
    double theta = degToRad(vfov);
    double h = tan(theta / 2);
    double viewportHeight = 2.0 * h;
    double viewportWidth = viewportHeight * aspectRatio;
    
    vec3 w = unitVector(lookfrom - lookat);
    vec3 u = unitVector(cross(vup, w));
    vec3 v = cross(w, u);

    origin = lookfrom;
    horizontal = u * viewportWidth;
    vertical = v * viewportHeight;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w;
}

ray camera::getRay(double s, double t) const {
    return ray(origin, lowerLeftCorner + s*horizontal + t*vertical - origin);
}
