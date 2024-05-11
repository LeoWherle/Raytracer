/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#pragma once

#include "IPrimitive.hpp"
#include "Math/MathsUtils.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"

class Cylinder : public IPrimitive {
    public:
        Point3D _origin;
        Vector3D _direction;
        float _radius;
        IMaterial *_material;
        float _height;

        Cylinder(const Point3D &origin, const Vector3D &direction, float radius, IMaterial *material, float height):
            _origin(origin),
            _direction(direction),
            _radius(radius),
            _material(material),
            _height(height)
        {
        }

        ~Cylinder() override = default;

        bool hits(const Ray& ray, Interval ray_max, HitRecord &rec) const override;

        void translate(const Point3D &trans);

        void rotate(const Point3D &degrees);
};
