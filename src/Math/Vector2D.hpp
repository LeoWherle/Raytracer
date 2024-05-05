/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Vector2D
*/

#pragma once
#include "Vector3D.hpp"
#include <cmath>

class Vector2D {
public:
    Vector2D() = default;
    Vector2D(float x, float y):
        _x(x),
        _y(y) {};
    ~Vector2D() = default;

    float _x = 0;
    float _y = 0;

    inline float length() const { return sqrt(_x * _x + _y * _y); };

    inline float length_squared() const { return _x * _x + _y * _y; };

    inline Vector2D &normalize() { return *this /= length(); };

    inline float dot(const Vector2D &other) const { return _x * other._x + _y * other._y; };
    inline Vector2D cross(const Vector2D &other) const
    {
        return Vector2D(_x * other._y - _y * other._x, _y * other._x - _x * other._y);
    };

    inline Vector2D normal(const Vector3D &other) const
    {
        return Vector2D(_x * other._y - _y * other._x, _y * other._x - _x * other._y);
    };

    inline Vector2D unit() const { return *this / length(); };

    inline Vector2D operator+(const Vector2D &other) const { return Vector2D(_x + other._x, _y + other._y); };

    inline Vector2D &operator+=(const Vector2D &other)
    {
        _x += other._x;
        _y += other._y;
        return *this;
    };

    inline Vector2D operator-(const Vector2D &other) const { return Vector2D(_x - other._x, _y - other._y); };

    inline Vector2D &operator-=(const Vector2D &other)
    {
        _x -= other._x;
        _y -= other._y;
        return *this;
    };

    inline Vector2D operator*(float scalar) const { return Vector2D(_x * scalar, _y * scalar); };

    inline Vector2D &operator*=(float scalar)
    {
        _x *= scalar;
        _y *= scalar;
        return *this;
    };

    inline Vector2D operator/(float scalar) const { return Vector2D(_x / scalar, _y / scalar); };

    inline Vector2D &operator/=(float scalar)
    {
        _x /= scalar;
        _y /= scalar;
        return *this;
    };

protected:
private:
};
