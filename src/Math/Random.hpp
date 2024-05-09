/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Random
*/

#pragma once

#include <cstdint>
#include <random>
#include <thread>

#include "Math/Vector3D.hpp"
#include "Xoroshiro.hpp"

class Random {
public:
    static auto gen_int() -> std::uint32_t { return s_RNG(); }

    static inline float gen_float(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(s_RNG);
    }

    static inline float gen_float()
    // Converts given uint32 value into a 32-bit floating
    // point value in the range of [0.0f, 1.0f)
    {
        return static_cast<float>(s_RNG() >> 8) * 0x1.0p-24f;
    }

    static inline Vector3D gen_vec(float min, float max)
    {
        return Vector3D(gen_float(min, max), gen_float(min, max), gen_float(min, max));
    }

    static inline Vector3D gen_vec() { return Vector3D(gen_float(), gen_float(), gen_float()); }

    static inline Vector3D unit_sphere()
    {
        Vector3D p;
        do {
            p = gen_vec(-1.0f, 1.0f);
        } while (p.length_squared() >= 1.0f);
        return p;
    }

    static inline Vector3D unit_vector() { return unit_sphere().unit(); }

protected:
private:
    static thread_local Xoshiro128Plus s_RNG;
};
