/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"

Point3D Rectangle3D::pointAt(float u, float v) const
{
    if (u < 0 || u > 1 || v < 0 || v > 1) {
        throw std::runtime_error(
            "u and v must be between 0 and 1 but: " + std::to_string(u) + " " + std::to_string(v)
        );
    }

    return _origin + _bottom_side * u + _left_side * v;
}
