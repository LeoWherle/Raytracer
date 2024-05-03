/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ILight
*/

#pragma once

#include "Color.hpp"
#include "Math/Point3D.hpp"

class ILight {
public:
    ILight(
        const Point3D &origin = Point3D(0, 0, 0), double intensity = 1,
        const Color &color = Color(255, 255, 255)
    ):
        _origin(origin),
        _intensity(intensity),
        _color(color)
    {
    }

    virtual ~ILight() = default;

    inline void move(const Vector3D &direction) { _origin = _origin + direction; }

    Point3D _origin;
    double _intensity;
    Color _color;
};
