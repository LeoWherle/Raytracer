/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#pragma once

#include "IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"

class Plane : public IPrimitive {
public:
    Point3D _origin;
    Vector3D _normal;
    IMaterial *_material;

    Plane(const Point3D &origin, const Vector3D &normal, IMaterial *material):
        _origin(origin),
        _normal(normal),
        _material(material)
    {
    }
    ~Plane() { delete _material; }

    bool hits(const Ray &r, Interval ray_max, HitRecord &rec) const override;

    void translate(const Point3D &trans);

    void rotate(const Point3D &degrees);
};
