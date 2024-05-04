/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** MetalMaterial
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

class MetalMaterial : public IMaterial {
  public:
    MetalMaterial(const Color& color, double fuzz) : color(color), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        Vector3D reflected = Vector3D::reflect(r_in.direction(), rec.normal);
        reflected = Vector3D::unit(reflected) + (mathsUtils::random_unit_vector() * fuzz);
        scattered = Ray(rec.p, reflected, r_in.time());
        attenuation = color;
        return (scattered.direction().dot(rec.normal) > 0);
    }

  private:
    Color color;
    double fuzz;
};
