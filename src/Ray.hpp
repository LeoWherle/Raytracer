/*
** EPITECH PROJECT, 2024
** $
** File description:
** Ray
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

class Ray {
public:
public:
    Ray() = default;

    Ray(const Point3D &origin, const Vector3D &direction):
        _origin(origin),
        _direction(direction)
    {
    }

    const Point3D &origin() const;
    const Vector3D &direction() const;


    Point3D at(float t) const;

private:
    Point3D _origin;
    Vector3D _direction;
};
