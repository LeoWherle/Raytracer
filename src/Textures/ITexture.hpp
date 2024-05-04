/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ITexture
*/

#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Point3D.hpp"

class ITexture {
  public:
    virtual ~ITexture() = default;

    virtual Color value(double u, double v, const Point3D& point) const = 0;
};
