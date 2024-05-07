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
    float _x = 0;
    float _y = 0;
    float _z = 0;

    Point3D() = default;
    Point3D(float x, float y, float z):
        _x(x),
        _y(y),
        _z(z) {};

    Point3D operator+(const Vector3D &vector) const;

    Point3D operator-(const Vector3D &vector) const;

    Vector3D operator-(const Point3D &point) const;
};
