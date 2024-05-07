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
    float size() const;

    bool contains(float x) const;

    bool surrounds(float x) const;

    float clamp(float x) const;
    Interval expand(float delta) const;

    static const Interval empty, universe;
};

Interval operator+(const Interval &ival, float displacement);
Interval operator+(float displacement, const Interval &ival);