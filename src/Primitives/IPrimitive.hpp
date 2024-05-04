/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IPrimitive
*/

#pragma once
#include "Color.hpp"
#include "Ray.hpp"
#include "Interval.hpp"
#include "HitRecord.hpp"

class IPrimitive {
public:
    virtual ~IPrimitive() = default;

    virtual bool hits(const Ray &r, Interval ray_max, HitRecord &rec) const = 0;
};
