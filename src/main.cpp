#include<iostream>
#include <Vec3/vec3.h>
#include <Vec3/color.h>

int main(){
    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = image_height-1; j >= 0; j--){
        std::cerr << "Scanning for " << j << " more inputs....." << "\r";
        for(int i = 0; i <= image_width-1; i++){
            Color3 pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            writeColor(std::cout, pixel_color);
        }
    }
    std::cerr << "\r\nDone.";
    return 0;
}