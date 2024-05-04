/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** HitRecord
*/

#pragma once

#include "Math/Vector3D.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include "Materials/IMaterial.hpp"
#include <memory>

class HitRecord {
  public:
    Point3D p;
    Vector3D normal;
    std::shared_ptr<IMaterial> material;
    double t;
    double u;
    double v;
    bool front_face;

    void set_face_normal(const Ray& ray, const Vector3D& out_normal) {
        front_face = out_normal.dot(ray.direction()) < 0;
        normal = front_face ? out_normal : -out_normal;
    }
};
