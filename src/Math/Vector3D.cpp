/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Vector3D
*/

#include "Vector3D.hpp"

std::ostream &operator<<(std::ostream &os, const Vector3D &point)
{
    os << "V(" << point._x << ", " << point._y << ", " << point._z << ")";
    return os;
}