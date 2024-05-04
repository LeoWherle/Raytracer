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
#include "AMaterial.hpp"
#include "HitRecord.hpp"
#include "MathsUtils.hpp"
#include "Textures/ITexture.hpp"
#include "Textures/SolidColorTexture.hpp"
#include <memory>

class BaseMaterial : public AMaterial {
  public:
    // Constructor that takes a Color and creates a SolidColorTexture from it
    BaseMaterial(const Color& color) : texture(std::make_shared<SolidColorTexture>(color)) {}

    // Constructor that takes a shared pointer to an ITexture
    BaseMaterial(std::shared_ptr<ITexture> texture) : texture(texture) {}

    // Method to scatter a ray. Takes in a Ray, a HitRecord, a Color for attenuation, and a Ray for scattered
    // Returns a boolean indicating if the scatter was successful
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        // Calculate scatter direction
        auto scatter_direction = rec.normal + mathsUtils::random_unit_vector();

        // If scatter direction is near zero, set it to the normal
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        // Set scattered to a new Ray with the scatter direction
        scattered = Ray(rec.p, scatter_direction, r_in.time());

        // Set attenuation to the value of the texture at the hit point
        attenuation = texture->value(rec.u, rec.v, rec.p);

        // Return true indicating scatter was successful
        return true;
    }

  private:
    std::shared_ptr<ITexture> texture;
};
