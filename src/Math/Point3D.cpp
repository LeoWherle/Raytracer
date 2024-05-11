/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Point3D
*/

#include "Point3D.hpp"

#ifdef USING_POINT3D
std::ostream &operator<<(std::ostream &os, const Point3D &point)
{
    os << "P(" << point._x << ", " << point._y << ", " << point._z << ")";
    return os;
}
#endif // USING_POINT3D