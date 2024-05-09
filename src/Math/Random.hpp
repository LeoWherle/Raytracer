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

    static inline float gen_float(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(s_RandomEngine);
    }

    static inline float gen_float()
    {
        return s_Distribution(s_RandomEngine);
    }

    static inline Vector3D gen_vec(float min, float max)
    {
        return Vector3D(gen_float(min, max), gen_float(min, max), gen_float(min, max));
    }

    static inline Vector3D gen_vec()
    {
        return Vector3D(gen_float(), gen_float(), gen_float());
    }

    static inline Vector3D unit_sphere()
    {
        Vector3D p;
        do {
            p = gen_vec(-1.0f, 1.0f);
        } while (p.length_squared() >= 1.0f);
        return p;
    }

    static inline Vector3D unit_vector()
    {
        return unit_sphere().unit();
    }

protected:
private:
    static thread_local std::mt19937 s_RandomEngine;
    static thread_local std::uniform_real_distribution<float> s_Distribution;
};
