/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** LightPoint
*/

#pragma once

#include "ILight.hpp"

class LightPoint : public ILight {
public:
    LightPoint() : ILight() {}
    LightPoint(const Point3D &origin) : ILight(origin) {}
    LightPoint(const Point3D &origin, double intensity) : ILight(origin, intensity) {}
    ~LightPoint() = default;
};
