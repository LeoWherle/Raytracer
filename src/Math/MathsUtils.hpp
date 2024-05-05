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

static float degrees_to_radians(float degrees) { return degrees * M_PIf / 180.0f; }

static float random_float() { return (float)rand() / ((float)RAND_MAX + 1.0f); }

inline Vector3D random_in_unit_sphere()
{
    while (true) {
        auto p = Vector3D::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

inline Vector3D random_unit_vector() { return Vector3D::unit(random_in_unit_sphere()); }
};
