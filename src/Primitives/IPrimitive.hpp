/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IPrimitive
*/

#pragma once
#include "Color.hpp"
#include "HitRecord.hpp"
#include "Math/Interval.hpp"
#include "Math/AABB.hpp"
#include "Ray.hpp"

class IPrimitive {
public:
    virtual ~IPrimitive() = default;

    virtual bool hits(const Ray &r, Interval ray_max, HitRecord &rec) const = 0;

    virtual AABB boundingBox() const = 0;
    virtual Point3D centroid() const = 0;
};
