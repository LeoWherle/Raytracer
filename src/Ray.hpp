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

    inline const Point3D &origin() const
    {
        return _origin;
    }

    inline const Vector3D &direction() const
    {
        return _direction;
    }

    inline Point3D at(float t) const
    {
        return _origin + _direction * t;
    }

private:
    Point3D _origin;
    Vector3D _direction;
};
