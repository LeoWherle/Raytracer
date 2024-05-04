/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IMarterial
*/

#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Math/Point3D.hpp"
#include "IMaterial.hpp"

class HitRecord;

class AMaterial : public IMaterial {
  public:
    virtual ~AMaterial() = default;

    virtual Color emitted(double u, double v, const Point3D& point) const {
        return Color(0,0,0);
    }

    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const {
        return false;
    }
};
