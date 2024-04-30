/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ILight
*/

#pragma once

#include "Math/Point3D.hpp"

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

    virtual ~ILight() = default;

    Point3D _origin = Point3D(0, 0, 0);
    double _intensity = 1;
};
