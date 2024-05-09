#pragma once

#include <cmath>

#include "Vector3D.hpp"
#include "Point3D.hpp"

class Matrix3D {
public:

    Matrix3D() = default;
    Matrix3D(const float matrix[3][3]);


    static Matrix3D rotation(const Vector3D &axis, float angle);

    Vector3D operator*(const Vector3D &other) const;
#ifdef USING_POINT3D
    Point3D operator*(const Point3D &other) const;
#endif // USING_POINT3D
private:
    float _matrix[3][3];
};
