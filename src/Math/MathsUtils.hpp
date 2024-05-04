/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Maths Utils
*/

#pragma once

#include "Vector3D.hpp"
#include <cmath>

namespace mathsUtils {

static double degrees_to_radians(double degrees) { return degrees * M_PI / 180.0; }

static double random_double() { return rand() / (RAND_MAX + 1.0); }

static double random_double(double min, double max) { return min + (max - min) * random_double(); }

static double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

inline Vector3D random_in_unit_sphere()
{
    while (true) {
        auto p = Vector3D::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

inline Vector3D random_in_unit_disks()
{
    while (true) {
        auto p = Vector3D(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

inline Vector3D random_unit_vector() { return Vector3D::unit(random_in_unit_sphere()); }
};
