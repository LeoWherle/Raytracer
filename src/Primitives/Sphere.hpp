/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Sphere
*/

#pragma once

#include "IPrimitive.hpp"
#include "Materials/IMaterial.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include <memory>

class Sphere : public IPrimitive {
private:
    Point3D origin;
    double _radius;
    std::shared_ptr<IMaterial> material;
    Vector3D origin_vec;

public:
    Sphere(const Point3D &center, double radius, std::shared_ptr<IMaterial> mat):
        origin(center),
        _radius(fmax(0, radius)),
        material(mat)
    {
    }

    bool hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const override
    {
        /* formula:
        * ray = origin + t * direction
        * sphere = (x - center)^2 + (y - center)^2 + (z - center)^2 = radius^2
        * substitute ray into sphere equation
        * (origin + t * direction - center)^2 = radius^2
        * a = direction * direction
        * b = 2 * direction * (origin - center)
        * c = (origin - center) * (origin - center) - radius^2
        * discriminant = b^2 - 4ac
        * if discriminant < 0, no real roots
        * if discriminant = 0, one real root
        * if discriminant > 0, two real roots
        * roots = (-b +- sqrt(discriminant)) / 2a
        */
        Vector3D oc = origin - ray.origin();
        auto a = ray.direction().length_squared();
        auto b = ray.direction().dot(oc);
        auto c = oc.length_squared() - _radius * _radius;

        auto discriminant = b * b - a * c;
        if (discriminant < 0) {
            return false;
        }

        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (b - sqrtd) / a;
        if (!ray_d.surrounds(root)) {
            root = (b + sqrtd) / a;
            if (!ray_d.surrounds(root))
                return false;
        }

        hitrec.t = root;
        hitrec.p = ray.at(hitrec.t);
        Vector3D outward_normal = (hitrec.p - origin) / _radius;
        hitrec.set_face_normal(ray, outward_normal);
        get_sphere_uv(outward_normal, hitrec.u, hitrec.v);
        hitrec.material = material;

        return true;
    }

    void get_sphere_uv(const Vector3D &p, double &u, double &v) const
    {
        auto theta = acos(-p._y);
        auto phi = atan2(-p._z, p._x) + M_PI;

        u = phi / (2 * M_PI);
        v = theta / M_PI;
    }
};
