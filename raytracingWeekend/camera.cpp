#include "camera.h"

camera::camera() {
	const double aspectRatio = 16.0 / 9.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * aspectRatio;
    double focalLength = 1.0;

    origin = point3(0);
    horizontal = vec3(viewportWidth, 0, 0);
    vertical = vec3(0, viewportHeight, 0);
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);
}

ray camera::getRay(double u, double v) const {
    return ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
}
