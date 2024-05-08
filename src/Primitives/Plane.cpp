/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Plane
*/

#include "Plane.hpp"

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
