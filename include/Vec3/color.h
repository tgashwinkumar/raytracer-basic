#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void writeColor(std::ostream& out, Color3 pixelColor){
    out << static_cast<int>(255.999 * pixelColor.x()) << ' '
        << static_cast<int>(255.999 * pixelColor.y()) << ' '
        << static_cast<int>(255.999 * pixelColor.z()) << '\n';
}

#endif
