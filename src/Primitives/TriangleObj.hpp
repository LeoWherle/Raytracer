/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** TriangleObj
*/

#pragma once

#include <array>
#include <limits>
#include <memory>

#include "IPrimitive.hpp"
#include "Materials/IMaterial.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

class TriangleObj : public IPrimitive {
    std::array<Point3D, 3> _vertices;
    std::array<Vector3D, 3> _normals;
    IMaterial *_material;

public:
    TriangleObj(
        const Point3D &v0, const Point3D &v1, const Point3D &v2, const Vector3D &n0, const Vector3D &n1,
        const Vector3D &n2, IMaterial *mat
    ):
        _vertices({v0, v1, v2}),
        _normals({n0, n1, n2}),
        _material(mat)
    {
    }
    TriangleObj(std::array<Point3D, 3> vertices, std::array<Vector3D, 3> normals, IMaterial *mat):
        _vertices(vertices),
        _normals(normals),
        _material(mat)
    {
    }

    ~TriangleObj() { }

    bool hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const override;

    AABB boundingBox() const override
    {
        Point3D min(
            std::fmin(_vertices[0]._x, std::fmin(_vertices[1]._x, _vertices[2]._x)),
            std::fmin(_vertices[0]._y, std::fmin(_vertices[1]._y, _vertices[2]._y)),
            std::fmin(_vertices[0]._z, std::fmin(_vertices[1]._z, _vertices[2]._z))
        );
        Point3D max(
            std::fmax(_vertices[0]._x, std::fmax(_vertices[1]._x, _vertices[2]._x)),
            std::fmax(_vertices[0]._y, std::fmax(_vertices[1]._y, _vertices[2]._y)),
            std::fmax(_vertices[0]._z, std::fmax(_vertices[1]._z, _vertices[2]._z))
        );
        return AABB(
            Interval(min._x, max._x),
            Interval(min._y, max._y),
            Interval(min._z, max._z)
        );
    }

    Point3D centroid() const override
    {
        return (_vertices[0] + _vertices[1] + _vertices[2]) / 3;
    }
};