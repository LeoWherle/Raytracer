/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Rectangle3D.hpp"
#include "Ray.hpp"

class Plane {
    public:

        Point3D _origin;
        Vector3D _plane;

        Plane(const Point3D &origin, const Vector3D &plane):
            _origin(origin),
            _plane(plane)
        {
        };

        bool hits(const Ray &ray) const;
};
