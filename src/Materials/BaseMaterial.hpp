/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** BaseMaterial
*/

#pragma once

#include "AMaterial.hpp"
#include "Color.hpp"
#include "HitRecord.hpp"
#include "Math/Point3D.hpp"
#include "Math/Random.hpp"
#include "Ray.hpp"
#include "Textures/ITexture.hpp"
#include "Textures/SolidColorTexture.hpp"
#include <memory>

class BaseMaterial : public AMaterial {
public:
    // Constructor that takes a Color and creates a SolidColorTexture from it
    BaseMaterial(const Color &color):
        _texture(std::make_unique<SolidColorTexture>(color))
    {
    }

    // Constructor that takes a shared pointer to an ITexture
    BaseMaterial(std::unique_ptr<ITexture> texture):
        _texture(std::move(texture))
    {
    }

    // Method to scatter a ray. Takes in a Ray, a HitRecord, a Color for attenuation, and a Ray for scattered
    // Returns a boolean indicating if the scatter was successful
    bool scatter(const Ray &, const HitRecord &rec, Color &attenuation, Ray &scattered) const override
    {
        // Calculate scatter direction
        auto scatter_direction = rec.normal + Random::unit_vector();

        // If scatter direction is near zero, set it to the normal
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        // Set scattered to a new Ray with the scatter direction
        scattered = Ray(rec.p, scatter_direction);

        // Set attenuation to the value of the texture at the hit point
        attenuation = _texture->value(rec.u, rec.v, rec.p);

        // Return true indicating scatter was successful
        return true;
    }

private:
    std::unique_ptr<ITexture> _texture;
};
