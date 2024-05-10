/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Triangle
*/

#include "Triangle.hpp"
#include "Math/MathsUtils.hpp"

bool Triangle::hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const
{
    const float EPSILON = std::numeric_limits<float>::epsilon();
        Vector3D edge1 = _v1 - _v0;
        Vector3D edge2 = _v2 - _v0;

        Vector3D pvec = ray.direction().cross(edge2);
        float det = edge1.dot(pvec);
        if (det > -EPSILON && det < EPSILON)
            return false;

        float inv_det = static_cast<float>(1.0 / det);
        Vector3D tvec = ray.origin() - _v0;
        float u = inv_det * tvec.dot(pvec);
        if (u < 0.0 || u > 1.0)
            return false;

        Vector3D qvec = tvec.cross(edge1);
        float v = inv_det * ray.direction().dot(qvec);
        if (v < 0.0 || u + v > 1.0)
            return false;

        float t = inv_det * edge2.dot(qvec);
        if (t > EPSILON && ray_d.surrounds(t)) {
            hitrec.t = t;
            hitrec.p = ray.at(t);
            hitrec.normal = _normal;
            hitrec.material = _material;
            return true;
        }
    return false;
}

void Triangle::translate(const Point3D &trans)
{
    _v0 += trans;
    _v1 += trans;
    _v2 += trans;
}

static void applyRot(Point3D &pos, const float Mx[3][3], const float My[3][3], const float Mz[3][3])
{
    pos = Point3D(Mx[0][0] * pos._x + Mx[0][1] * pos._y + Mx[0][2] * pos._z,
        Mx[1][0] * pos._x + Mx[1][1] * pos._y + Mx[1][2] * pos._z,
        Mx[2][0] * pos._x + Mx[2][1] * pos._y + Mx[2][2] * pos._z);
    pos = Point3D(My[0][0] * pos._x + My[0][1] * pos._y + My[0][2] * pos._z,
        My[1][0] * pos._x + My[1][1] * pos._y + My[1][2] * pos._z,
        My[2][0] * pos._x + My[2][1] * pos._y + My[2][2] * pos._z);
    pos = Point3D(Mz[0][0] * pos._x + Mz[0][1] * pos._y + Mz[0][2] * pos._z,
        Mz[1][0] * pos._x + Mz[1][1] * pos._y + Mz[1][2] * pos._z,
        Mz[2][0] * pos._x + Mz[2][1] * pos._y + Mz[2][2] * pos._z);
}

void Triangle::rotate(const Point3D &degrees)
{
    float x = mathsUtils::degrees_to_radians(degrees._x);
    float y = mathsUtils::degrees_to_radians(degrees._y);
    float z = mathsUtils::degrees_to_radians(degrees._z);

    float mx[3][3] = {{1,0,0}, {0,cosf(x),-sinf(x)}, {0,sinf(x),cosf(x)}};
    float my[3][3] = {{cosf(y),0,sinf(y)}, {0,1,0}, {-sinf(y),0,cosf(y)}};
    float mz[3][3] = {{cosf(z),-sinf(z),0}, {sinf(z),cosf(z),0}, {0,0,1}};

    applyRot(_v0, mx, my, mz);
    applyRot(_v1, mx, my, mz);
    applyRot(_v2, mx, my, mz);
    applyRot(_normal, mx, my, mz);
}
