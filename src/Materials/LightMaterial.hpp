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
#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include "Textures/ITexture.hpp"
#include "ILight.hpp"
#include "Textures/SolidColorTexture.hpp"
#include <memory>

class LightMaterial : public AMaterial, public ILight {
public:
    LightMaterial(std::unique_ptr<ITexture> tex, float intensity = 1.0f):
        texture(std::move(tex)),
        _intensity(intensity)
    {
    }
    LightMaterial(const Color &emit, float intensity = 1.0f):
        texture(std::make_unique<SolidColorTexture>(emit)),
        _intensity(intensity)
    {
    }
    ~LightMaterial() = default;

    Color emitted(float u, float v, const Point3D &p) const override
    {
        return texture->value(u, v, p) * _intensity;
    }

private:
    std::unique_ptr<ITexture> texture;
    float _intensity;
};
