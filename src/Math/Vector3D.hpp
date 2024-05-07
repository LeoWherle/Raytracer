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

    float length() const;
    float length_squared() const;
    Vector3D &normalize();

    float dot(const Vector3D &other) const;

    Vector3D cross(const Vector3D &other) const;

    Vector3D unit() const;
    static Vector3D unit(const Vector3D &v);

    bool near_zero() const;

    static Vector3D reflect(const Vector3D &v, const Vector3D &n);

    Vector3D operator-() const;

    Vector3D operator-(const Vector3D &other) const;

    Vector3D &operator-=(const Vector3D &other);

    Vector3D operator+(const Vector3D &other) const;

    Vector3D &operator+=(const Vector3D &other);

    Vector3D operator*(const Vector3D &other) const;

    Vector3D &operator*=(const Vector3D &other);

    Vector3D operator*(float scalar) const;

    Vector3D &operator*=(float scalar);

    Vector3D operator/(float scalar) const;

    Vector3D &operator/=(float scalar);

protected:
private:
};
