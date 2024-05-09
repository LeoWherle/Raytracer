#pragma once

#include <cmath>
#include <ostream>

#include "Vector3D.hpp"
#include "Point3D.hpp"

class Matrix3D {
public:

    Matrix3D() = default;
    Matrix3D(const float matrix[3][3]);


    static Matrix3D rotation(const Vector3D &axis, float angle);

    Vector3D operator*(const Vector3D &other) const;

    Point3D operator*(const Point3D &other) const;


    friend std::ostream &operator << (std::ostream &os, const Matrix3D &mat)
    {
        auto sep = "  /  ";

        os << "Matrix :" << std::endl;
        os << "| "<< mat._matrix[0][0] << sep << mat._matrix[0][1] << sep << mat._matrix[0][2] << std::endl;
        os << "| "<< mat._matrix[1][0] << sep << mat._matrix[1][1] << sep << mat._matrix[1][2] << std::endl;
        os << "| "<< mat._matrix[2][0] << sep << mat._matrix[2][1] << sep << mat._matrix[2][2] << std::endl;

        return os;
    }
private:
    float _matrix[3][3];
};
