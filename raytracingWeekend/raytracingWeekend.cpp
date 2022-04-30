#include <iostream>
#include "vec3.h"
#include "color.h"

int main() {
    // Image size
    const int imageWidth = 256;
    const int imageHeight = 256;

    // Renderer
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n"; // Colors in ASCII << Imagesize << Maxcolor 255

    // (0,0) is in bottom left of the image
    for (int j = imageHeight-1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            color pixelColor(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0.25);
            writeColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone!";
}