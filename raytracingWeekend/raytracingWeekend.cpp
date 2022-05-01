#include <iostream>
#include "rtweekend.h"
#include "hittableList.h"
#include "color.h"
#include "sphere.h"

/**
* Calculate a color for the ray. When compared to rays next to each other, they form a gradient.
* @param r A ray to get the color from.
* @return A color for this ray. 
*/
color rayColor(const ray& r, const hittable& world) {
    hitRecord rec;
    if (world.hit(r, 0, infinity, rec))
        return 0.5 * (rec.normal + color(1));

    // Background
    vec3 unitDirection = unitVector(r.direction());
    auto t = 0.5 * (unitDirection.y() + 1);
    return (1.0 - t) * color(1.0) + t * color(0.5, 0.7, 1.0); // LERP the colors
}

int main() {
    // Image size
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // World
    hittableList world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));        // Add sphere
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));   // Add "ground"

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
            color pixelColor = rayColor(r, world);
            writeColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone!";
}