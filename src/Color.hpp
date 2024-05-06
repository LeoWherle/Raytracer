/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Color
*/

#pragma once

#include "Interval.hpp"
#include "Math/Vector3D.hpp"
#include <cstdint>

class Color {
public:
    Color() = default;
    Color(float r, float g, float b):
        _r(r),
        _g(g),
        _b(b)
    {
    }
    ~Color() = default;

    float _r = 0;
    float _g = 0;
    float _b = 0;

    inline Color operator*(const float nb) const { return Color(_r * nb, _g * nb, _b * nb); }

    inline Color &operator*=(const float nb)
    {
        _r *= nb;
        _g *= nb;
        _b *= nb;
        return *this;
    }

    inline Color operator/(const float nb) const { return Color(_r / nb, _g / nb, _b / nb); }

    inline Color &operator/=(const float nb)
    {
        _r /= nb;
        _g /= nb;
        _b /= nb;
        return *this;
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

    inline Color operator*(const Color &color) const
    {
        return Color(_r * color._r, _g * color._g, _b * color._b);
    }

    inline uint8_t getR() const { return static_cast<uint8_t>(_r * 256); }

    inline uint8_t getG() const { return static_cast<uint8_t>(_g * 256); }

    inline uint8_t getB() const { return static_cast<uint8_t>(_b * 256); }

    Color to_gamma() const
    {
        return Color(
            (_r > 0 ? std::sqrt(_r) : 0),
            (_g > 0 ? std::sqrt(_g) : 0),
            (_b > 0 ? std::sqrt(_b) : 0)
        );
    }

    Color to_linear() const { return Color(_r * _r, _g * _g, _b * _b); }

    Color clamp() const
    {
        static const Interval intensity(0.000f, 0.999f);

        return Color {
            intensity.clamp(_r),
            intensity.clamp(_g),
            intensity.clamp(_b),
        };
    }
};
