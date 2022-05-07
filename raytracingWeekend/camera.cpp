#include "camera.h"

camera::camera(point3 lookfrom, point3 lookat, vec3 vup, const double vfov, const double aspectRatio, const double aperture, const double focusDist) {
    double theta = degToRad(vfov);
    double h = tan(theta / 2);
    double viewportHeight = 2.0 * h;
    double viewportWidth = viewportHeight * aspectRatio;
    
    w = unitVector(lookfrom - lookat);
    u = unitVector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = u * viewportWidth * focusDist;
    vertical = v * viewportHeight * focusDist;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w * focusDist;

    lensRadius = aperture / 2;
}

ray camera::getRay(double s, double t) const {
    vec3 rd = lensRadius * randomInUnitDisk();
    vec3 offset = u * rd.x() + v * rd.y();
    return ray(origin + offset, lowerLeftCorner + s*horizontal + t*vertical - origin - offset);
}
