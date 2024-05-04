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
#include "ITexture.hpp"

class SolidColorTexture : public ITexture {
  public:
    SolidColorTexture(const Color& color) : _color(color) {}

    SolidColorTexture(double red, double green, double blue) : SolidColorTexture(Color(red,green,blue)) {}

    Color value(double u, double v, const Point3D& p) const override {
        return _color;
    }

  private:
    Color _color;
};
