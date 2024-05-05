/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** AMarterial
*/

#pragma once

#include "Color.hpp"
#include "IMaterial.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

class HitRecord;

class AMaterial : public IMaterial {
public:
    virtual ~AMaterial() = default;

    virtual Color emitted(float, float, const Point3D &) const { return Color(0, 0, 0); }

    virtual bool scatter(const Ray &, const HitRecord &, Color &, Ray &) const { return false; }
};
