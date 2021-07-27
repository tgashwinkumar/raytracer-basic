
#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class Sphere : public Hittable{
public:
    Point3 centerPoint;
    double radius;

public:
    Sphere(Point3 center, double r): centerPoint(center), radius(r) {};

    virtual bool isRayHit(const Ray& r, double t_min, double t_max, HitRecord& hitRecord) const override  {
        Vec3 oc = r.origin - this->centerPoint;
        auto a = dot(r.direction, r.direction);
        auto half_b = dot(oc, r.direction);
        auto c = dot(oc, oc) - this->radius * this->radius;
        auto discriminant = half_b * half_b - a * c;
        
        if (discriminant < 0) return false;

        auto sqrtD = std::sqrt(discriminant);
        auto root = (-half_b - sqrtD)/a;

        if(root < t_min || root > t_max){
            root = (-half_b + sqrtD) / a;
            if (root < t_min || root > t_max){
                return false;
            }
        }

        hitRecord.t = root;
        hitRecord.point = r.getPointAt(root);
        Vec3 outwardNormal = (hitRecord.point - this->centerPoint)/this->radius;
        hitRecord.setFaceNormal(r, outwardNormal);

        return true;
    }
};

#endif