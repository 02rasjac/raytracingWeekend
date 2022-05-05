#include <iostream>
#include "rtweekend.h"
#include "hittableList.h"
#include "color.h"
#include "sphere.h"
#include "camera.h"

/**
* Calculate a color for the ray. When compared to rays next to each other, they form a gradient.
* @param r A ray to get the color from.
* @return A color for this ray. 
*/
color rayColor(const ray& r, const hittable& world, int depth) {
    hitRecord rec;

    // Return black if too deep
    if (depth <= 0) return color(0);

    if (world.hit(r, 0, infinity, rec)) {
        point3 target = rec.p + rec.normal + randomInUnitSphere();
        return 0.5 * rayColor(ray(rec.p, target - rec.p), world, --depth);
    }

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
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    // World
    hittableList world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));        // Add sphere
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));   // Add "ground"

    // Camera
    camera cam;

    // Renderer
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n"; // Colors in ASCII << Imagesize << Maxcolor 255

    // (0,0) is in bottom left of the image
    for (int j = imageHeight-1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            color pixelColor(0);
            for (int s = 0; s < samplesPerPixel; s++) {
                double u = double(i) / (imageWidth - 1);
                double v = double(j) / (imageHeight - 1);
                pixelColor += rayColor(cam.getRay(u, v), world, maxDepth);
            }

            writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone!";
}