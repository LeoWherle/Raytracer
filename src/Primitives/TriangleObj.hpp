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
};