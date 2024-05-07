/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Color
*/

#include "Color.hpp"

Color Color::operator*(const float nb) const
{
    return Color(_r * nb, _g * nb, _b * nb);
}

Color &Color::operator*=(const float nb)
{
    _r *= nb;
    _g *= nb;
    _b *= nb;
    return *this;
}

Color Color::operator/(const float nb) const
{
    return Color(_r / nb, _g / nb, _b / nb);
}

Color &Color::operator/=(const float nb)
{
    _r /= nb;
    _g /= nb;
    _b /= nb;
    return *this;
}

Color Color::operator+(const Color &color) const
{
    return Color(_r + color._r, _g + color._g, _b + color._b);
}

Color Color::operator+=(const Color &color)
{
    _r += color._r;
    _g += color._g;
    _b += color._b;
    return *this;
}

Color Color::operator*(const Color &color) const
{
    return Color(_r * color._r, _g * color._g, _b * color._b);
}

uint8_t Color::getR() const
{
    return static_cast<uint8_t>(_r * 256);
}

uint8_t Color::getG() const
{
    return static_cast<uint8_t>(_g * 256);
}

uint8_t Color::getB() const
{
    return static_cast<uint8_t>(_b * 256);
}

Color Color::to_gamma() const
{
    return Color(
        (_r > 0 ? std::sqrt(_r) : 0),
        (_g > 0 ? std::sqrt(_g) : 0),
        (_b > 0 ? std::sqrt(_b) : 0)
    );
}

Color Color::to_linear() const
{
    return Color(_r * _r, _g * _g, _b * _b);
}

Color Color::clamp() const
{
    static const Interval intensity(0.000f, 0.999f);
    return Color {
        intensity.clamp(_r),
        intensity.clamp(_g),
        intensity.clamp(_b),
    };
}
