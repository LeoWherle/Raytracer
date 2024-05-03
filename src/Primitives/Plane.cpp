/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#include "Plane.hpp"

double Plane::hits(const Ray &ray) const
{
    float denom = _normal.dot(ray._direction);

    if (denom == 0.0)
        return -1;

    float t = (_origin - ray._origin).dot(_normal) / denom;

    if (t < 0.0)
        return -1;
    return t;
}