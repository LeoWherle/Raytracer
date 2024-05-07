/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#include "Plane.hpp"

bool Plane::hits(const Ray &r, Interval ray_max, HitRecord &rec) const
{
    auto denom = _normal.dot(r.direction());

    if (denom == 0)
        return false;

    auto t = (_origin - r.origin()).dot(_normal) / denom;

    if (t < 0.0 || !ray_max.surrounds(t))
        return false;

    rec.t = t;
    rec.p = r.at(t);
    rec.normal = _normal;
    rec.material = _material;
    return true;
}
