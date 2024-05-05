/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ITexture
*/

#pragma once

#include "Color.hpp"
#include "ITexture.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

class SolidColorTexture : public ITexture {
public:
    SolidColorTexture(const Color &color):
        _color(color)
    {
    }

    SolidColorTexture(float red, float green, float blue):
        SolidColorTexture(Color(red, green, blue))
    {
    }

    Color value(float, float, const Point3D &) const override { return _color; }

private:
    Color _color;
};
