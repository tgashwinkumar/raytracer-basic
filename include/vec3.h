#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3
{
public:
    double e[3];

public:
    Vec3() : e{0, 0, 0} {}
    Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() { return e[0]; }
    double y() { return e[1]; }
    double z() { return e[2]; }

    Vec3 operator-() const {
        return Vec3(-e[0], -e[1], -e[2]);
    }

    double operator[](int i) const {
        return e[i];
    }

    double &operator[](int i){
        return e[i];
    }

    Vec3 operator+=(const Vec3 &v){
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3 operator*=(const double k){
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
        return *this;
    }

    Vec3 operator*=(const Vec3 &v){
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }

    Vec3 operator/=(const double k){
        return *this *= 1 / k;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline static Vec3 random(){
        return Vec3(random_double(), random_double(), random_double());
    }

    inline static Vec3 random(double min, double max){
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool near_zero() const {
        const auto s = 1e-8;
        return fabs(this->e[0]) < s && fabs(this->e[1]) > s && fabs(this->e[2]) > s;
    }
};


inline std::ostream& operator<< (std::ostream &out, const Vec3& v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v){
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v){
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v){
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v){
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t){
    return t * v;
}

inline Vec3 operator/(const Vec3& v, double t){
    return (1 / t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v){
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v){
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(const Vec3 &v){
    return v / v.length();
}

Vec3 random_in_unit_sphere(){
    while (true)
    {
        auto p = Vec3::random(-1, 1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

Vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_hemisphere(const Vec3& normal){
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else return -in_unit_sphere;
}

Vec3 reflect(const Vec3& incident, const Vec3& normal){
    return incident - 2 * dot(incident, normal) * normal;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -std::sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

using Point3 = Vec3;
using Color3 = Vec3;

#endif