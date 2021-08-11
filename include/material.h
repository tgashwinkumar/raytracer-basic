#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils.h"
#include "hittable.h"

class Material {
public:
    virtual bool isScattered(const Ray &r_in, const HitRecord &record, Color3 &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material {
public:
    Color3 albedo;

public:
    Lambertian(const Color3 &albe) : albedo(albe){};

    virtual bool isScattered(const Ray &r_in, const HitRecord &record, Color3 &attenuation, Ray &scattered) const override {
        auto scatter_direction = record.normal + random_unit_vector();
        if (scatter_direction.near_zero())
        {
            scatter_direction = record.normal;
        }
        scattered = Ray(record.point, scatter_direction);
        attenuation = this->albedo;
        return true;
    }
};

class Metal : public Material {
public:
    Color3 albedo;
    double fuzz;

public:
    Metal(const Color3 &a, double fzz) : albedo(a), fuzz(fzz < 1 ? fzz : 1){};

    virtual bool isScattered(const Ray &r_in, const HitRecord &record, Color3 &attenuation, Ray &scattered) const override {
        Vec3 reflected = reflect(unit_vector(r_in.direction), record.normal);
        scattered = Ray(record.point, reflected + this->fuzz * random_in_unit_sphere());
        attenuation = this->albedo;
        return dot(scattered.direction, record.normal) > 0;
    }
};

class Dielectric : public Material {
public:
    double ir;

private:
    static double reflectance(double cosine, double ref_idx) {
        // Schlick's approximation
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

public:
    Dielectric(double index_of_refraction) : ir(index_of_refraction){};

    virtual bool isScattered(const Ray &r_in, const HitRecord &record, Color3 &attenuation, Ray &scattered) const override {
        attenuation = Color3(1.0, 1.0, 1.0);
        double refraction_ratio = record.frontFace ? (1.0 / this->ir) : this->ir;

        Vec3 unit_direction = unit_vector(r_in.direction);
        double cos_theta = fmin(dot(-unit_direction, record.normal), 1.0);
        double sin_theta = sqrt(1 - cos_theta * cos_theta);
        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        Vec3 refracted;
        if (cannot_refract || this->reflectance(cos_theta, refraction_ratio) > random_double())
            refracted = reflect(unit_direction, record.normal);
        else
            refracted = refract(unit_direction, record.normal, refraction_ratio);

        scattered = Ray(record.point, refracted);
        return true;
    }
};

#endif