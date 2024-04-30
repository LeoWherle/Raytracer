/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Sphere
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Ray.hpp"

class Sphere {
public:
    Point3D _center;
    double _radius;
    Vector3D _color;

    Sphere(const Point3D &center, double radius, const Vector3D &color):
        _center(center),
        _radius(radius),
        _color(color)
    {
    }

    double hits(const Ray &ray) const
    {
        Vector3D oc = ray._origin - _center;
        double a = ray._direction.dot(ray._direction);
        double b = 2.0 * oc.dot(ray._direction);
        double c = oc.dot(oc) - _radius * _radius;
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return -1;
        }
        double t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (t < 0) {
            t = (-b + sqrt(discriminant)) / (2.0 * a);
        }
        return t;
    }
};