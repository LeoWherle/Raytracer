/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Interval
*/

#pragma once

class Interval {
public:
    float min, max;

    Interval();
    Interval(float min_, float max_);

    Interval(const Interval &a, const Interval &b);
    inline float size() const { return max - min; }

    inline bool contains(float x) const { return min <= x && x <= max; }

    inline bool surrounds(float x) const { return min < x && x < max; }

    inline float clamp(float x) const
    {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    inline Interval expand(float delta) const
    {
        auto padding = delta / 2;
        return Interval(min - padding, max + padding);
    }

    static const Interval empty, universe;
};

Interval operator+(const Interval &ival, float displacement);
Interval operator+(float displacement, const Interval &ival);