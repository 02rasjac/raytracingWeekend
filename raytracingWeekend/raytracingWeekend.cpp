#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

/*
* Checks whether a ray collides with a sphere.
* @param center Centerpoint of the sphere.
* @param radius Radius of the sphere.
* @param r The ray to check collision with.
* @return Parameter t on the ray r that first hit the sphere. If no collison, then returns -1.0.
*/
double hitSphere(const point3& center, const double radius, const ray& r) {
    vec3 oc = r.origin() - center; // Vector from origin to center
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0; // Did not hit the sphere
    } 
    return (-b - sqrt(discriminant)) / (2.0 * a); // Return t from at^2 + bt + c = 0
}

/**
* Calculate a color for the ray. When compared to rays next to each other, they form a gradient.
* @param r A ray to get the color from.
* @return A color for this ray. 
*/
color rayColor(const ray& r) {
    point3 sphereCenter(0, 0, -1);
    auto t = hitSphere(sphereCenter, 0.5, r);
    // Color based on normal for the sphere
    if (t > 0.0) { // hit sphere at r(t)
        auto normal = r.at(t) - sphereCenter;
        return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }
    // Background
    vec3 unitDirection = unitVector(r.direction());
    t = 0.5 * (unitDirection.y() + 1);
    return (1.0 - t) * color(1.0) + t * color(0.5, 0.7, 1.0); // LERP the colors
}

int main() {
    // Image size
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // Camera
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * aspectRatio;
    double focalLength = 1.0;

    point3 origin = point3(0);
    vec3 horizontal = vec3(viewportWidth, 0, 0);
    vec3 vertical = vec3(0, viewportHeight, 0);
    point3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

    // Renderer
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n"; // Colors in ASCII << Imagesize << Maxcolor 255

    // (0,0) is in bottom left of the image
    for (int j = imageHeight-1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            double u = double(i) / (imageWidth - 1);
            double v = double(j) / (imageHeight - 1);
            ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone!";
}