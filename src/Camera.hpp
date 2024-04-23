/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Camera
*/

#pragma once

#include "Point3D.hpp"
#include "Ray.hpp"
#include "Rectangle3D.hpp"

class Camera {
public:
    Camera():
        _origin(Point3D(0, 0, 0)),
        _screen(Rectangle3D(Point3D(0, 0, 1), Vector3D(1, 0, 0), Vector3D(0, 1, 0)))
    {
    }
    Camera(const Point3D &origin, const Rectangle3D &screen):
        _origin(origin),
        _screen(screen)
    {
    }

    Ray ray(double u, double v) const
    {
        Point3D point = _screen.pointAt(u, v);
        Vector3D direction = point - _origin;
        return Ray(_origin, direction);
    }

private:
    Point3D _origin;
    Rectangle3D _screen;
};
