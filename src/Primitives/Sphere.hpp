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
    float _radius;
    IMaterial *material;

public:
    Sphere(const Point3D &center, float radius, IMaterial* mat):
        origin(center),
        _radius((float)fmax(0, radius)),
        material(mat)
    {
    }
    ~Sphere()
    {
        delete material;
    }

    bool hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const override;

    void get_sphere_uv(const Vector3D &p, float &u, float &v) const;

    void translate(const Point3D &trans);

    AABB boundingBox() const override
    {
        Point3D min(
            origin._x - _radius,
            origin._y - _radius,
            origin._z - _radius
        );
        Point3D max(
            origin._x + _radius,
            origin._y + _radius,
            origin._z + _radius
        );
        return AABB(
            Interval(min._x, max._x),
            Interval(min._y, max._y),
            Interval(min._z, max._z)
        );
    }

    Point3D centroid() const override
    {
        return origin;
    }
};
