/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Random
*/

#include "Random.hpp"
#include "Xoroshiro.hpp"

thread_local Xoshiro128Plus Random::s_RNG;
