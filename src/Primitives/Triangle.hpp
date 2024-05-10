/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Triangle
*/

#pragma once

#include <array>
#include <memory>
#include <limits>

#include "IPrimitive.hpp"
#include "Materials/IMaterial.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

class Triangle : public IPrimitive {
private:
    // Vertices of the triangle
    Point3D _v0;
    Point3D _v1;
    Point3D _v2;
    Vector3D _normal;
    IMaterial *_material;

public:
    Triangle(const Point3D &v0, const Point3D &v1, const Point3D &v2, IMaterial *mat):
        _v0(v0),
        _v1(v1),
        _v2(v2),
        _material(mat)
    {
        _normal = (v1 - v0).cross(v2 - v0).normalize();
    }
    ~Triangle()
    {
        delete _material;
    }

    // Möller-Trumbore intersection algorithm
    // https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
    bool hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const override;

    void translate(const Point3D &trans);

    AABB boundingBox() const override
    {
        Point3D min(
            std::fmin(_v0._x, std::fmin(_v1._x, _v2._x)),
            std::fmin(_v0._y, std::fmin(_v1._y, _v2._y)),
            std::fmin(_v0._z, std::fmin(_v1._z, _v2._z))
        );
        Point3D max(
            std::fmax(_v0._x, std::fmax(_v1._x, _v2._x)),
            std::fmax(_v0._y, std::fmax(_v1._y, _v2._y)),
            std::fmax(_v0._z, std::fmax(_v1._z, _v2._z))
        );
        return AABB(
            Interval(min._x, max._x),
            Interval(min._y, max._y),
            Interval(min._z, max._z)
        );
    }

    Point3D centroid() const override
    {
        return (_v0 + _v1 + _v2) / 3;
    }

    void rotate(const Point3D &degrees);

protected:
private:
};
