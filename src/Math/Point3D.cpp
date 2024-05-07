/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Point3D
*/

#include "Point3D.hpp"

Point3D Point3D::operator+(const Vector3D &vector) const
{
    return Point3D(_x + vector._x, _y + vector._y, _z + vector._z);
}

Point3D Point3D::operator-(const Vector3D &vector) const
{
    return Point3D(_x - vector._x, _y - vector._y, _z - vector._z);
}

Vector3D Point3D::operator-(const Point3D &point) const
{
    return Vector3D(_x - point._x, _y - point._y, _z - point._z);
}
