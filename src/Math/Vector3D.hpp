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
    Vector3D(float x, float y, float z):
        _x(x),
        _y(y),
        _z(z) {};
    ~Vector3D() = default;

    float _x = 0;
    float _y = 0;
    float _z = 0;

    inline float length() const { return std::sqrt(_x * _x + _y * _y + _z * _z); }
    inline float length_squared() const { return _x * _x + _y * _y + _z * _z; }
    inline Vector3D &normalize() { return *this /= length(); }

    inline float dot(const Vector3D &other) const { return _x * other._x + _y * other._y + _z * other._z; }

    Vector3D cross(const Vector3D &other) const
    {
        return Vector3D(
            _y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x
        );
    }

    inline Vector3D unit() const { return *this / length(); }
    static inline Vector3D unit(const Vector3D &v) { return v / v.length(); }

    static inline Vector3D random(float min, float max)
    {
        return Vector3D(
            min + (max - min) * (float)rand() / ((float)RAND_MAX + 1.0f), min + (max - min) * (float)rand() / ((float)RAND_MAX + 1.0f),
            min + (max - min) * (float)rand() / ((float)RAND_MAX + 1.0f)
        );
    }

    bool near_zero() const
    {
        // Return true if the vector is close to zero in all dimensions.
        auto s = 1e-8;
        return (fabs(_x) < s) && (fabs(_y) < s) && (fabs(_z) < s);
    }

    static inline Vector3D reflect(const Vector3D &v, const Vector3D &n) { return v - (n * (v.dot(n) * 2)); }

    inline Vector3D operator-() const { return Vector3D(-_x, -_y, -_z); }

    inline Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(_x + other._x, _y + other._y, _z + other._z);
    }

    inline Vector3D &operator+=(const Vector3D &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    inline Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(_x - other._x, _y - other._y, _z - other._z);
    }

    inline Vector3D &operator-=(const Vector3D &other)
    {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    inline Vector3D operator*(const Vector3D &other) const
    {
        return Vector3D(
            _y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x
        );
    }

    inline Vector3D &operator*=(const Vector3D &other)
    {
        _x = _y * other._z - _z * other._y;
        _y = _z * other._x - _x * other._z;
        _z = _x * other._y - _y * other._x;
        return *this;
    }

    inline Vector3D operator*(float scalar) const { return Vector3D(_x * scalar, _y * scalar, _z * scalar); }

    inline Vector3D &operator*=(float scalar)
    {
        _x *= scalar;
        _y *= scalar;
        _z *= scalar;
        return *this;
    }

    inline Vector3D operator/(float scalar) const { return *this * (1 / scalar); }

    inline Vector3D &operator/=(float scalar)
    {
        _x /= scalar;
        _y /= scalar;
        _z /= scalar;
        return *this;
    }

protected:
private:
};
