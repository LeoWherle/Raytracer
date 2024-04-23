/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Point3D
*/

#pragma once

#include "Vector3D.hpp"

class Point3D {
public:
    double _x = 0;
    double _y = 0;
    double _z = 0;

    Point3D() = default;
    Point3D(double x, double y, double z):
        _x(x),
        _y(y),
        _z(z) {};

    Point3D operator+(const Vector3D &vector) const
    {
        return Point3D(_x + vector._x, _y + vector._y, _z + vector._z);
    }

    Vector3D operator-(const Point3D &point) const
    {
        return Vector3D(_x - point._x, _y - point._y, _z - point._z);
    }
};
