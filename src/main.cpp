#include<iostream>

#include "utils.h"
#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"

Color3 getRayColor(const Ray& r, const Hittable& world, int depth){
    HitRecord record;

    if(depth <= 0)
        return Color3(0.0, 0.0, 0.0);

    if(world.isRayHit(r, 0.001, infinity, record)) {
        Ray scattered;
        Color3 attenuation;
        if(record.mat_ptr->isScattered(r, record, attenuation, scattered))
            return attenuation * getRayColor(scattered, world, depth-1);
        return Color3(0.0, 0.0, 0.0);
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

    auto material_ground = make_shared<Lambertian>(Color3(0.8, 0.8, 0.3));
    auto material_cen = make_shared<Lambertian>(Color3(0.1, 0.4, 0.7));
    auto material_left = make_shared<Dielectric>(1.4);
    auto material_right = make_shared<Metal>(Color3(0.0, 1.0, 0.2), 0.1);

    HittableList world;
    world.add(make_shared<Sphere>(Point3(0,0,-1), 0.5, material_cen));
    world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), -0.4, material_left));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_right));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100, material_ground));

    Camera cam(Point3(0.0, 0.0, 1.0));

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = image_height-1; j >= 0; j--){
        std::cerr << "Scanning for " << j << " more inputs....." << "\r";
        for(int i = 0; i <= image_width-1; i++){
            Color3 pixelColor(0,0,0);
            for(int s = 0; s < samples_per_pixel; s++){
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.getRay(u, v);
                pixelColor += getRayColor(r, world, max_depth);
            }
            writeColor(std::cout, pixelColor, samples_per_pixel);
        }
    }
    std::cerr << "\r\nDone.";
    return 0;
}