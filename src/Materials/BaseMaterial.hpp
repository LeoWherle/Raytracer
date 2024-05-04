/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** BaseMaterial
*/

#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Point3D.hpp"
#include "IMaterial.hpp"
#include "HitRecord.hpp"
#include "MathsUtils.hpp"
#include "Textures/ITexture.hpp"
#include "Textures/SolidColorTexture.hpp"
#include <memory>

class BaseMaterial : public IMaterial {
  public:
    BaseMaterial(const Color& color) : texture(std::make_shared<SolidColorTexture>(color)) {}
    BaseMaterial(std::shared_ptr<ITexture> texture) : texture(texture) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        auto scatter_direction = rec.normal + mathsUtils::random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction, r_in.time());
        attenuation = texture->value(rec.u, rec.v, rec.p);
        return true;
    }

  private:
    std::shared_ptr<ITexture> texture;
};
