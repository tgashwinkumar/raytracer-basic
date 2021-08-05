#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void writeColor(std::ostream& out, Color3 pixelColor, int samples_per_pixel){

    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    auto scale = 1.0 / samples_per_pixel;
    r  = std::sqrt(r*scale);
    g  = std::sqrt(g*scale);
    b  = std::sqrt(b*scale);

    out << static_cast<int>(256*clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256*clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256*clamp(b, 0.0, 0.999)) << '\n';
}

#endif
