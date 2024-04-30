/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IPrimitive
*/

#pragma once
#include "Color.hpp"
#include "Ray.hpp"

class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        virtual double hits(const Ray &) const = 0;
};
