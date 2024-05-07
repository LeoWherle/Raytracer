/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Vector3D
*/

#include "Vector3D.hpp"

float Vector3D::length() const
{
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

float Vector3D::length_squared() const
{
    return _x * _x + _y * _y + _z * _z;
}

Vector3D &Vector3D::normalize()
{
    return *this /= length();
}

float Vector3D::dot(const Vector3D &other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
    return Vector3D(
        _y * other._z - _z * other._y,
        _z * other._x - _x * other._z,
        _x * other._y - _y * other._x
    );
}

Vector3D Vector3D::unit() const
{
    return *this / length();
}

Vector3D Vector3D::unit(const Vector3D &v)
{
    return v / v.length();
}

bool Vector3D::near_zero() const
{
    // Return true if the vector is close to zero in all dimensions.
    auto s = 1e-8;
    return (fabs(_x) < s) && (fabs(_y) < s) && (fabs(_z) < s);
}

Vector3D Vector3D::reflect(const Vector3D &v, const Vector3D &n)
{
    return v - (n * (v.dot(n) * 2));
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-_x, -_y, -_z);
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(_x - other._x, _y - other._y, _z - other._z);
}

Vector3D &Vector3D::operator-=(const Vector3D &other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(_x + other._x, _y + other._y, _z + other._z);
}

Vector3D &Vector3D::operator+=(const Vector3D &other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

Vector3D Vector3D::operator*(float scalar) const
{
    return Vector3D(_x * scalar, _y * scalar, _z * scalar);
}

Vector3D &Vector3D::operator*=(float scalar)
{
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    return *this;
}

Vector3D Vector3D::operator*(const Vector3D &other) const
{
    return Vector3D (
        _y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x
    );
}

Vector3D &Vector3D::operator*=(const Vector3D &other)
{
    _x = _y * other._z - _z * other._y;
    _y = _z * other._x - _x * other._z;
    _z = _x * other._y - _y * other._x;
    return *this;
}

Vector3D Vector3D::operator/(float scalar) const
{
    return *this * (1 / scalar);
}

Vector3D &Vector3D::operator/=(float scalar)
{
    _x /= scalar;
    _y /= scalar;
    _z /= scalar;
    return *this;
}
