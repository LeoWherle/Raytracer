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

    SolidColorTexture(double red, double green, double blue):
        SolidColorTexture(Color(red, green, blue))
    {
    }

    Color value(double, double, const Point3D &) const override { return _color; }

private:
    Color _color;
};
