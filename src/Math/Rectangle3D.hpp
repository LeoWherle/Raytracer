/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Rectange3D
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <stdexcept>

class Rectangle3D {
public:
    Point3D _origin;
    Vector3D _bottom_side;
    Vector3D _left_side;

    Rectangle3D() = default;
    Rectangle3D(const Point3D &origin, const Vector3D &bottom_side, const Vector3D &left_side):
        _origin(origin),
        _bottom_side(bottom_side),
        _left_side(left_side)
    {
    }

    Point3D pointAt(double u, double v) const
    {
        if (u < 0 || u > 1 || v < 0 || v > 1) {
            throw std::runtime_error(
                "u and v must be between 0 and 1 but: " + std::to_string(u) + " " + std::to_string(v)
            );
        }

        return _origin + _bottom_side * u + _left_side * v;
    }
};
