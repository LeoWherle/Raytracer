/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#include "Plane.hpp"
#include "Math/MathsUtils.hpp"
#include "Math/Matrix3D.hpp"

inline void get_plane_uv(const Point3D &p, const Vector3D &normal, float &u, float &v)
{
    Vector3D a = normal.cross(Vector3D(1, 0, 0));
    Vector3D b = normal.cross(Vector3D(0, 1, 0));

    Vector3D max_ab = a.dot(a) < a.dot(b) ? b : a;

    Vector3D c = normal.cross(Vector3D(0, 0, 1));

    Vector3D u_vec = (max_ab.dot(max_ab) < c.dot(c) ? c : max_ab).normalize();
    Vector3D v_vec = normal.cross(u_vec);

    u = u_vec._x * p._x + u_vec._y * p._y + u_vec._z * p._z;
    v = v_vec._x * p._x + v_vec._y * p._y + v_vec._z * p._z;
}

bool Plane::hits(const Ray &r, Interval ray_max, HitRecord &rec) const
{
    auto denom = _normal.dot(r.direction());

    if (denom == 0)
        return false;

    auto t = (_origin - r.origin()).dot(_normal) / denom;

    if (t < 0.0 || !ray_max.surrounds(t))
        return false;

    rec.t = t;
    rec.p = r.at(t);
    rec.normal = _normal;
    rec.material = _material;
    get_plane_uv(rec.p, _normal, rec.u, rec.v);
    return true;
}

void Plane::translate(const Point3D &trans)
{
    _origin += trans;
}

// TODO: fix _normal
void Plane::rotate(const Point3D &degrees)
{
    float x = mathsUtils::degrees_to_radians(degrees._x);
    float y = mathsUtils::degrees_to_radians(degrees._y);
    float z = mathsUtils::degrees_to_radians(degrees._z);

    float mx[3][3] = {{1,0,0}, {0,cosf(x),-sinf(x)}, {0,sinf(x),cosf(x)}};
    float my[3][3] = {{cosf(y),0,sinf(y)}, {0,1,0}, {-sinf(y),0,cosf(y)}};
    float mz[3][3] = {{cosf(z),-sinf(z),0}, {sinf(z),cosf(z),0}, {0,0,1}};

    Matrix3D x_mat(mx);
    //std::clog << x_mat << std::endl;
    Matrix3D y_mat(my);
    //std::clog << y_mat << std::endl;
    Matrix3D z_mat(mz);
    //std::clog << z_mat << std::endl;

    //std::clog << (x_mat * _normal) << std::endl;
    _normal = x_mat * _normal;
    //std::clog << (y_mat * _normal) << std::endl;
    _normal = y_mat * _normal;
    //std::clog << (z_mat * _normal) << std::endl;
    _normal = z_mat * _normal;
}
