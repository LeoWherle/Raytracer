/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Random
*/

#include "Random.hpp"

thread_local std::mt19937 Random::s_RandomEngine;
thread_local std::uniform_real_distribution<float> Random::s_Distribution;

void Random::init()
{
    s_RandomEngine.seed(std::random_device()());
}

float Random::gen_float(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(s_RandomEngine);
}

float Random::gen_float()
{
    return s_Distribution(s_RandomEngine);
}

Vector3D Random::gen_vec(float min, float max)
{
    return Vector3D(gen_float(min, max), gen_float(min, max), gen_float(min, max));
}

Vector3D Random::gen_vec()
{
    return Vector3D(gen_float(), gen_float(), gen_float());
}

Vector3D Random::unit_sphere()
{
    Vector3D p;
    do {
        p = gen_vec(-1.0f, 1.0f);
    } while (p.length_squared() >= 1.0f);
    return p;
}

Vector3D Random::unit_vector()
{
    return unit_sphere().unit();
}
