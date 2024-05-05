/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Point2D
*/

#pragma once
#include "Vector2D.hpp"

class Point2D {
public:
    Point2D() = default;
    Point2D(float x, float y):
        _x(x),
        _y(y) {};

    ~Point2D() = default;

    float _x = 0;
    float _y = 0;

    Point2D operator+(const Vector2D &vector) const { return Point2D(_x + vector._x, _y + vector._y); }

    Vector2D operator-(const Point2D &point) const { return Vector2D(_x - point._x, _y - point._y); }

protected:
private:
};
