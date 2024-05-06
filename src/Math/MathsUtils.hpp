/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Maths Utils
*/

#pragma once

#include "Vector3D.hpp"
#include <cmath>

#include <random>

namespace mathsUtils {

static float degrees_to_radians(float degrees) { return degrees * M_PIf / 180.0f; }

static float random_float()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}

inline Vector3D random_in_unit_sphere()
{
    Vector3D p;
    do {
        p = Vector3D::random(-1, 1);
    } while (p.length_squared() >= 1);
    return p;
}

inline Vector3D random_unit_vector() { return Vector3D::unit(random_in_unit_sphere()); }
};
