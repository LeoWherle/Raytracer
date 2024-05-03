/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#pragma once

#include "Math/Vector3D.hpp"
#include "IPrimitive.hpp"
#include "Ray.hpp"

class Plane : public IPrimitive{
    public:

        Vector3D _normal;
        Point3D _origin;

        Plane(Point3D origin, Vector3D normal) :_origin(origin), _normal(normal)
        {
        };

        double hits(const Ray &ray) const override;
};
