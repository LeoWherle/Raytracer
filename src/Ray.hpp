/*
** EPITECH PROJECT, 2024
** $
** File description:
** Ray
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

class Ray {
public:
    Point3D _origin;
    Vector3D _direction;
    Point3D _color;

    Ray() = default;
    Ray(const Point3D &origin, const Vector3D &direction):
        _origin(origin),
        _direction(direction)
    {
    }

    Point3D at(double t) const { return _origin + _direction * t; }
};
