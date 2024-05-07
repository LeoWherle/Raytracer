/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Random
*/

#pragma once

#include <random>
#include <thread>

#include "Math/Vector3D.hpp"

class Random {
public:
    static void init();

    static float gen_float();

    static float gen_float(float min, float max);

    static Vector3D gen_vec();

    static Vector3D gen_vec(float min, float max);

    static Vector3D unit_sphere();

    static Vector3D unit_vector();

protected:
private:
    static thread_local std::mt19937 s_RandomEngine;
    static thread_local std::uniform_real_distribution<float> s_Distribution;
};
