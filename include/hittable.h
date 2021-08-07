#ifndef HITTABLE_H
#define HITTABLE_H

#include <iostream>
#include "vec3.h"
#include "ray.h"

class Material;

struct HitRecord{
    Point3 point;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    bool frontFace;

    inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal) {
        frontFace = dot(r.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable{
    public:
        virtual bool isRayHit(const Ray& r, double t_min, double t_max, HitRecord& hitRecord) const = 0;
};

#endif