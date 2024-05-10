/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** Cone
*/

#include "Cone.hpp"
#include <cmath>

Cone::Cone(const Point3D &tip, const Point3D &surface, const Vector3D &axis, IMaterial *material, const float &radius)
: _tip(tip), _surface(surface), _axis(axis), _material(material), _radius(radius)
{
}

Cone::~Cone()
{
}

bool Cone::hits(const Ray &r, Interval ray_max, HitRecord &rec) const
{
    float angle = atanf(_radius / (_surface - _tip).length());
    float cosa = pow(cos(angle), 2);
    float t, t1, t2;

    Vector3D CO = (r.origin() - _tip);

    float a = pow(r.direction().dot(_axis), 2) - cosa;
    float b = 2 * (r.direction().dot(_axis) * CO.dot(_axis) - r.direction().dot(CO) * cosa);
    float c = pow(CO.dot(_axis), 2) * CO.dot(CO) * cosa;

    float det = pow(b, 2) - 4 * a * c;

    if (det < 0) {
        return false;
    }

    float sqrtd = std::sqrt(det);

    float root = (b - sqrtd) / a;
    if (!ray_max.surrounds(root)) {
        root = (b + sqrtd) / a;
        if (!ray_max.surrounds(root))
            return false;
    }

    rec.t = root;               // intersection point according to space
    rec.p = r.at(rec.t);        // intersection point translated

    Vector3D outward_normal = Vector3D(
        2 * (rec.p._x - _tip._x),
        2 * (rec.p._y - _tip._y),
        2 * pow(tan(angle), 2) * (rec.p._z - _tip._z));

    rec.set_face_normal(r, outward_normal);
    rec.material = _material;
    return true;
}