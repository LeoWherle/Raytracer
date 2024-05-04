/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Color
*/

#pragma once

#include <cstdint>
#include "Math/Vector3D.hpp"

class Color {
public:
    Color() = default;
    Color(double r, double g, double b):
        _r(r),
        _g(g),
        _b(b)
    {}
    ~Color() = default;

    double _r = 0;
    double _g = 0;
    double _b = 0;

    inline Color operator*(const double nb) const
    {
        return Color(_r * nb, _g * nb, _b * nb);
    }

    inline Color operator/(const double nb) const
    {
        return Color(_r / nb, _g / nb, _b / nb);
    }

    inline Color operator+(const Color &color) const
    {
        return Color(_r + color._r, _g + color._g, _b + color._b);
    }

    inline Color operator+=(const Color &color)
    {
        _r += color._r;
        _g += color._g;
        _b += color._b;
        return *this;
    }

    inline uint8_t getR() const
    {
        return static_cast<uint8_t>(_r);
    }

    inline uint8_t getG() const
    {
        return static_cast<uint8_t>(_g);
    }

    inline uint8_t getB() const
    {
        return static_cast<uint8_t>(_b);
    }
};
