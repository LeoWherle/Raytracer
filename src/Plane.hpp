/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#pragma once

#include "Math/Point2D.hpp"
#include "Math/Vector2D.hpp"
#include "Math/Rectangle3D.hpp"
#include "Ray.hpp"

class Plane {
    public:

        Point2D _origin;
        Vector2D _plane;

        Plane(const Point2D &origin, const Vector2D &plane):
            _origin(origin),
            _plane(plane)
        {
        };

        bool hits(const Ray &ray) const;
};
