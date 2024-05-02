/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#pragma once

#include "IPrimitive.hpp"

class Cylinder : public IPrimitive {
    public:
        Point3D _origin;
        Vector3D _direction;
        double _radius;
        Color _color;

        inline Cylinder(const Point3D &origin, const Vector3D &direction, double radius, const Color &color):
            _origin(origin),
            _direction(direction),
            _radius(radius),
            _color(color)
        {
        }

        ~Cylinder() override = default;

        inline double hits(const Ray& ray) const override {
            Vector3D Rl = (ray._origin - _origin);
            Vector3D Ca = _direction;
            Vector3D Rd = ray._direction;
            double Cr = _radius;
            double a = 1 - Ca.dot(Rd) * Ca.dot(Rd);
            double b = 2 * (Rd.dot(Rl) - Ca.dot(Rd) * Ca.dot(Rl));
            double c = Rl.dot(Rl) - Ca.dot(Rl) * Ca.dot(Rl) - Cr * Cr;
            double discriminant = b * b - 4 * a * c;
            if (discriminant < 0) {
                return -1;
            }
            double t = (-b - sqrt(discriminant)) / (2.0 * a);
            if (t < 0) {
                t = (-b + sqrt(discriminant)) / (2.0 * a);
            }
            return t;
        };
};
