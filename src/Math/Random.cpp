/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Random
*/

#include "Random.hpp"
#include "Xoroshiro.hpp"

// thread_local uint64_t Random::s_State[2];
thread_local XoshiroCpp::Xoshiro128Plus Random::s_RNG;
// thread_local std::mt19937 Random::s_RandomEngine;
// thread_local std::uniform_real_distribution<float> Random::s_Distribution;

// void Random::init()
// {
//     s_RandomEngine.seed(std::random_device()());
// }
