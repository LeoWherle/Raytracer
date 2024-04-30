/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ILight
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"

class ILight {
public:
    ILight() = default;
    ILight(const Point3D &origin):
        _origin(origin)
    {}
    ILight(const Point3D &origin, double intensity):
        _origin(origin),
        _intensity(intensity)
    {}
    ILight(const Point3D &origin, double intensity, const Color &color):
        _origin(origin),
        _intensity(intensity),
        _color(color)
    {}

    virtual ~ILight() = default;

    inline void move(const Vector3D &direction)
    {
        _origin = _origin + direction;
    }

    Point3D _origin = Point3D(0, 0, 0);
    double _intensity = 1;
    Color _color = Color(255, 255, 255);
};
