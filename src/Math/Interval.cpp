/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Interval
*/

#include <limits>

#include "Interval.hpp"

Interval::Interval(float mn, float mx) : min(mn), max(mx)
{
}

Interval::Interval(const Interval &a, const Interval &b)
{
    min = a.min <= b.min ? a.min : b.min;
    max = a.max >= b.max ? a.max : b.max;
}

float Interval::size() const { return max - min; }

bool Interval::contains(float x) const { return min <= x && x <= max; }

bool Interval::surrounds(float x) const { return min < x && x < max; }

float Interval::clamp(float x) const
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

Interval Interval::expand(float delta) const
{
    auto padding = delta / 2;
    return Interval(min - padding, max + padding);
}

const Interval Interval::empty = Interval(+std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());

const Interval Interval::universe = Interval(-std::numeric_limits<float>::infinity(), +std::numeric_limits<float>::infinity());

Interval operator+(const Interval &ival, float displacement)
{
    return Interval(ival.min + displacement, ival.max + displacement);
}

Interval operator+(float displacement, const Interval &ival) { return ival + displacement; }