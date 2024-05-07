/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Color
*/

#pragma once

#include "Math/Interval.hpp"
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

    Color operator*(const float nb) const;

    Color &operator*=(const float nb);

    Color operator/(const float nb) const;

    Color &operator/=(const float nb);

    Color operator+(const Color &color) const;

    Color operator+=(const Color &color);

    Color operator*(const Color &color) const;

    uint8_t getR() const;

    uint8_t getG() const;

    uint8_t getB() const;

    Color to_gamma() const;

    Color to_linear() const;

    Color clamp() const;
};
