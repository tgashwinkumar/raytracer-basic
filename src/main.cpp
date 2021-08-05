#include<iostream>

#include "utils.h"
#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

Color3 getRayColor(const Ray& r, const Hittable& world, int depth){
    HitRecord record;

    if(depth <= 0)
        return Color3(0.0, 0.0, 0.0);

    if(world.isRayHit(r, 0, infinity, record)) {
        Point3 target = record.point + record.normal + random_in_unit_sphere();
        return 0.5*getRayColor(Ray(record.point, target - record.point), world, depth-1);
    }
    Vec3 unitDir = unit_vector(r.direction);
    auto t = 0.5*(unitDir.y() + 1.0);
    return (1.0 - t)*Color3(1.0, 1.0, 1.0) + t*Color3(0.5, 0.7, 1.0);
} 

int main(){

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    HittableList world;
    world.add(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    Camera cam;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = image_height-1; j >= 0; j--){
        std::cerr << "Scanning for " << j << " more inputs....." << "\r";
        for(int i = 0; i <= image_width-1; i++){
            Color3 pixelColor(0,0,0);
            for(int s = 0; s < samples_per_pixel; s++){
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                // auto u = i  / (image_width-1);
                // auto v = j / (image_height-1);
                Ray r = cam.getRay(u, v);
                pixelColor += getRayColor(r, world, max_depth);
            }
            writeColor(std::cout, pixelColor, samples_per_pixel);
        }
    }
    std::cerr << "\r\nDone.";
    return 0;
}