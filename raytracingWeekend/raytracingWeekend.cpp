#include <iostream>
#include "rtweekend.h"
#include "hittableList.h"
#include "color.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

/**
* Calculate a color for the ray. When compared to rays next to each other, they form a gradient.
* @param r A ray to get the color from.
* @return A color for this ray. 
*/
color rayColor(const ray& r, const hittable& world, int depth) {
    hitRecord rec;

    // Return black if too deep
    if (depth <= 0) return color(0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.matPtr->scatter(r, rec, attenuation, scattered))
            return attenuation * rayColor(scattered, world, --depth);
        return color(0, 0, 0);
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

    auto materialGround = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    //auto materialCenter = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    //auto materialLeft   = make_shared<metal>(color(0.8), 0.3);
    auto materialCenter = make_shared<dielectric>(2.4);
    auto materialLeft = make_shared<dielectric>(1.5);
    auto materialRight  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, materialGround)); // Add "ground"
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, materialCenter));      // Add sphere
    world.add(make_shared<sphere>(point3(-1.0, 0, -1), 0.5, materialLeft));     // Add sphere
    world.add(make_shared<sphere>(point3(1.0, 0, -1), 0.5, materialRight));     // Add sphere

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