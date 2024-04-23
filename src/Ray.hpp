/*
** EPITECH PROJECT, 2024
** $
** File description:
** Ray
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

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
};
