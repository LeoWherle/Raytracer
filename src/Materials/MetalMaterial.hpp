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
#include "AMaterial.hpp"
#include "HitRecord.hpp"
#include "MathsUtils.hpp"
#include "Textures/ITexture.hpp"
#include "Textures/SolidColorTexture.hpp"
#include <memory>

class MetalMaterial : public AMaterial {
  public:
    // Constructor that takes a Color and a fuzz factor for the material
    // If the fuzz factor is greater than 1, it is clamped to 1
    MetalMaterial(const Color& color, double fuzz) : color(color), fuzz(fuzz < 1 ? fuzz : 1) {}

    // Method to scatter a ray. Takes in a Ray, a HitRecord, a Color for attenuation, and a Ray for scattered
    // Returns a boolean indicating if the scatter was successful
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        // Calculate the reflected direction of the incoming ray
        Vector3D reflected = Vector3D::reflect(r_in.direction(), rec.normal);

        // Add a random unit vector scaled by the fuzz factor to the reflected direction
        reflected = Vector3D::unit(reflected) + (mathsUtils::random_unit_vector() * fuzz);

        // Set scattered to a new Ray with the reflected direction
        scattered = Ray(rec.p, reflected, r_in.time());

        // Set attenuation to the color of the material
        attenuation = color;

        // Return true if the dot product of the scattered direction and the normal is greater than 0
        // This indicates that the ray was scattered in the same hemisphere as the normal
        return (scattered.direction().dot(rec.normal) > 0);
    }

  private:
    Color color;
    // Fuzz factor of the material
    double fuzz;
};
