/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LightMaterial
*/

#pragma once

#include "AMaterial.hpp"
#include "Color.hpp"
#include "HitRecord.hpp"
#include "Math/MathsUtils.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include "Textures/ITexture.hpp"
#include "Textures/SolidColorTexture.hpp"
#include <memory>

class LightMaterial : public AMaterial {
public:
    LightMaterial(std::shared_ptr<ITexture> tex):
        texture(tex)
    {
    }
    LightMaterial(const Color &emit):
        texture(std::make_shared<SolidColorTexture>(emit))
    {
    }

    Color emitted(double u, double v, const Point3D &p) const override { return texture->value(u, v, p); }

private:
    std::shared_ptr<ITexture> texture;
};
