#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "vec3.h"
class Ray {
    public:
        Point3 origin;
        Vec3 direction;
    public:
        Ray(){}
        Ray(const Point3& orig, const Vec3& dir): origin(orig), direction(dir){}

        Point3 getOrigin() { return origin; }
        Vec3 getDirection() { return direction; }

        Point3 getPointAt(const double t){
            return origin + t * direction;
        }
};

#endif