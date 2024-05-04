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
    float radius;
    std::shared_ptr<IMaterial> material;
    Vector3D origin_vec;

    Sphere(const Point3D &center, const Point3D &center2, float radius, std::shared_ptr<IMaterial> mat):
        origin(center),
        radius(fmax(0, radius)),
        material(mat)
    {
    }

    bool hits(const Ray &r, Interval ray_d, HitRecord &hitrec) const override
    {
        Vector3D oc = origin - r.origin();
        auto a = r.direction().length_squared();
        auto h = r.direction().dot(oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0) {
            return false;
        }

        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!ray_d.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_d.surrounds(root))
                return false;
        }

        hitrec.t = root;
        hitrec.p = r.at(hitrec.t);
        Vector3D outward_normal = (hitrec.p - origin) / radius;
        hitrec.set_face_normal(r, outward_normal);
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
