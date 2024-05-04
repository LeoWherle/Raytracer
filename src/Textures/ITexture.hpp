/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ITexture
*/

#pragma once

#include "Color.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

class ITexture {
public:
    virtual ~ITexture() = default;

    virtual Color value(double u, double v, const Point3D &point) const = 0;
};
