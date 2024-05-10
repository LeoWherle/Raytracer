/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ILight
*/

#pragma once

#include "ILight.hpp"

class ALight : public ILight {
public:
    ALight() = default;
    ALight(const Point3D &origin):
        _origin(origin)
    {}
    ALight(const Point3D &origin, double intensity):
        _origin(origin),
        _intensity(intensity)
    {}

    ~ALight() = default;

    Point3D _origin = Point3D(0, 0, 0);
    double _intensity = 1;
};