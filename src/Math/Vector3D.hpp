/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Vector3D
*/

#pragma once

#include <cmath>
class Vector3D {
public:
    Vector3D() = default;
    Vector3D(double x, double y, double z):
        _x(x),
        _y(y),
        _z(z) {};
    ~Vector3D() = default;

    double _x = 0;
    double _y = 0;
    double _z = 0;

    double length() const { return std::sqrt(_x * _x + _y * _y + _z * _z); }
    double length_squared() const { return _x * _x + _y * _y + _z * _z; }

    double dot(const Vector3D &other) const { return _x * other._x + _y * other._y + _z * other._z; }

    Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(_x + other._x, _y + other._y, _z + other._z);
    }

    Vector3D &operator+=(const Vector3D &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(_x - other._x, _y - other._y, _z - other._z);
    }

    Vector3D &operator-=(const Vector3D &other)
    {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    Vector3D operator*(const Vector3D &other) const
    {
        return Vector3D(
            _y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x
        );
    }

    Vector3D &operator*=(const Vector3D &other)
    {
        _x = _y * other._z - _z * other._y;
        _y = _z * other._x - _x * other._z;
        _z = _x * other._y - _y * other._x;
        return *this;
    }

    Vector3D operator*(double scalar) const { return Vector3D(_x * scalar, _y * scalar, _z * scalar); }

    Vector3D &operator*=(double scalar)
    {
        _x *= scalar;
        _y *= scalar;
        _z *= scalar;
        return *this;
    }

    Vector3D operator/(double scalar) const { return Vector3D(_x / scalar, _y / scalar, _z / scalar); }

    Vector3D &operator/=(double scalar)
    {
        _x /= scalar;
        _y /= scalar;
        _z /= scalar;
        return *this;
    }

protected:
private:
};
