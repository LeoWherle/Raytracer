/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#pragma once

#include "IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"


class Plane : public IPrimitive {
public:
    Point3D _origin;
    Vector3D _normal;
    IMaterial *_material;

    Plane(const Point3D &origin, const Vector3D &normal, IMaterial *material):
        _origin(origin),
        _normal(normal),
        _material(material)
    {
    }

    // TODO
    bool hits(const Ray &r, Interval ray_max, HitRecord &rec) const override
    {
        auto denom = _normal.dot(r.direction());
        if (denom > 1e-6) {
            auto p0l0 = _origin - r.origin();
            auto t = p0l0.dot(_normal) / denom;
            if (t >= ray_max.min && t <= ray_max.max) {
                rec.t = t;
                rec.p = r.at(t);
                rec.normal = _normal;
                rec.material = _material;
                return true;
            }
        }
        return false;
    }
};
