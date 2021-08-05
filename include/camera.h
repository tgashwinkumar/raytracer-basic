#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

class Camera
{
private:
    Point3 origin;
    Point3 lowerLeft;
    Vec3 horizontal;
    Vec3 vertical;
public:
    Camera();

    Ray getRay(double u, double v) const;
};

Camera::Camera(){
    auto aspect_ratio = 16.0/ 9.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    this->origin = Point3(0, 0, 0);
    this->horizontal = Vec3(viewport_width, 0, 0);
    this->vertical = Vec3(0, viewport_height, 0);
    this->lowerLeft = this->origin - this->horizontal / 2 - this->vertical / 2 - Vec3(0, 0, focal_length);
}


Ray Camera::getRay(double u, double v) const {
    return Ray(this->origin, this->lowerLeft + u * this->horizontal + v * this->vertical - this->origin);
}

#endif