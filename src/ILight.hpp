/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ILight
*/

#pragma once

#include "Color.hpp"

class ILight {
public:
    virtual ~ILight() = default;

    virtual auto emitted(float u, float v, const Point3D &p) const -> Color = 0;
};
