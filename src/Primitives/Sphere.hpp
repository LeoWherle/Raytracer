/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Sphere
*/

#pragma once

#include "IPrimitive.hpp"
#include "Materials/IMaterial.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include <memory>

class Sphere : public IPrimitive {
private:
    Point3D origin;
    float _radius;
    IMaterial *material;
    Vector3D origin_vec;

public:
    Sphere(const Point3D &center, float radius, IMaterial *mat):
        origin(center),
        _radius((float)fmax(0, radius)),
        material(mat)
    {
    }
    ~Sphere()
    {
        delete material;
    }

    bool hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const override;

    void get_sphere_uv(const Vector3D &p, float &u, float &v) const;
};
