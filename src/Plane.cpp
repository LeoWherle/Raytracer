/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#include "Plane.hpp"

static Point2D random_point(const Point2D &origin, const Vector2D &plane)
{
    return Point2D(
        origin._x + (rand() % static_cast<int>(plane._x)),
        origin._y + (rand() % static_cast<int>(plane._y))
    );
}

bool Plane::hits(const Ray &ray) const
{
    Vector2D normal = _plane.normal(ray._direction);
    double numerator = (random_point(_origin, _plane) - _origin).dot(normal);
    double denominator = ray._direction.dot(Vector3D(normal._x, normal._y, 0));
    double t = numerator / denominator;

    if (t > 0)
        return true;
    return false;
}