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
    std::shared_ptr<IMaterial> _material;

public:
    Triangle(const Point3D &v0, const Point3D &v1, const Point3D &v2, std::shared_ptr<IMaterial> mat):
        _v0(v0),
        _v1(v1),
        _v2(v2),
        _material(mat)
    {
        _normal = (v1 - v0).cross(v2 - v0).normalize();
    }
    ~Triangle() = default;

    // Möller-Trumbore intersection algorithm
    // https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
    bool hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const override;

protected:
private:
};
