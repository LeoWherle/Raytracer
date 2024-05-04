/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Maths Utils
*/

#pragma once

#include <cmath>

namespace mathsUtils {

    static double degrees_to_radians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    static double random_double()
    {
        return rand() / (RAND_MAX + 1.0);
    }

    static double random_double(double min, double max)
    {
        return min + (max - min) * random_double();
    }

    static double clamp(double x, double min, double max)
    {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }
};
