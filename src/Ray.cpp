/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Ray
*/

#include "Ray.hpp"

const Point3D &Ray::origin() const
{
    return _origin;
}

const Vector3D &Ray::direction() const
{
    return _direction;
}

Point3D Ray::at(float t) const
{
    return _origin + _direction * t;
}
