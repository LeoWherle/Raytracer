/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Matrix3D
*/

#include "Matrix3D.hpp"

Matrix3D::Matrix3D(const float matrix[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            _matrix[i][j] = matrix[i][j];
}

Matrix3D Matrix3D::rotation(const Vector3D &axis, float angle)
{
    float result[3][3];
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    float oneMinusCosAngle = 1 - cosAngle;

    float x = axis._x;
    float y = axis._y;
    float z = axis._z;

    result[0][0] = cosAngle + x * x * oneMinusCosAngle;
    result[0][1] = x * y * oneMinusCosAngle - z * sinAngle;
    result[0][2] = x * z * oneMinusCosAngle + y * sinAngle;

    result[1][0] = y * x * oneMinusCosAngle + z * sinAngle;
    result[1][1] = cosAngle + y * y * oneMinusCosAngle;
    result[1][2] = y * z * oneMinusCosAngle - x * sinAngle;

    result[2][0] = z * x * oneMinusCosAngle - y * sinAngle;
    result[2][1] = z * y * oneMinusCosAngle + x * sinAngle;
    result[2][2] = cosAngle + z * z * oneMinusCosAngle;

    return Matrix3D(result);
}

Vector3D Matrix3D::operator*(const Vector3D &other) const
{
    Vector3D result;
    result._x = _matrix[0][0] * other._x + _matrix[0][1] * other._y + _matrix[0][2] * other._z;
    result._y = _matrix[1][0] * other._x + _matrix[1][1] * other._y + _matrix[1][2] * other._z;
    result._z = _matrix[2][0] * other._x + _matrix[2][1] * other._y + _matrix[2][2] * other._z;

    return result;
}
#ifdef USING_POINT3D
Point3D Matrix3D::operator*(const Point3D &other) const
{
    Point3D result;
    result._x = _matrix[0][0] * other._x + _matrix[0][1] * other._y + _matrix[0][2] * other._z;
    result._y = _matrix[1][0] * other._x + _matrix[1][1] * other._y + _matrix[1][2] * other._z;
    result._z = _matrix[2][0] * other._x + _matrix[2][1] * other._y + _matrix[2][2] * other._z;
    return result;
}
#endif // USING_POINT3D