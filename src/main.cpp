#include<iostream>
#include "vec3.h"
#include "color.h"
#include <ray.h>
   

Color3 getRayColor(Ray& r){
    Vec3 unitDir = unit_vector(r.getDirection());
    auto t = 0.5*(unitDir.y() + 1.0);
    return (1.0 - t)*Color3(1.0, 1.0, 1.0) + t*Color3(1.0, 0.7, 0.2);
} 

int main(){

    const auto aspect_ratio = 16.0 / 9.0;

    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lowerLeft = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);


    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = image_height-1; j >= 0; j--){
        std::cerr << "Scanning for " << j << " more inputs....." << "\r";
        for(int i = 0; i <= image_width-1; i++){
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            Ray r(origin, lowerLeft + u*horizontal + v*vertical - origin);
            Color3 pixelColor = getRayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }
    std::cerr << "\r\nDone.";
    return 0;
}