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

    Point3D pointAt(float u, float v) const;
};
