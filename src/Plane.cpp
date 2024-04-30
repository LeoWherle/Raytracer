/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#include "Plane.hpp"

Plane::Plane(const Point3D &origin, const Vector3D &thickness, const Vector3D &width, const Vector3D &height, const Vector3D &size):
    _origin(origin),
    _thickness(thickness),
    _width(width),
    _height(height),
    _size(size)
{
}

bool Plane::hits(const Ray &ray) const
{
    //i have a Point3d that is the origin and a Vector3d that is the plane, do a fucntion to check if the ray hits the plane

    Vector3D normal = _plane.normalize();
    float denom = normal.dot(ray._direction);

    return false;
}