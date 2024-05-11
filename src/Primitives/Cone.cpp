/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** Cone
*/

#include "Cone.hpp"
#include "Math/MathsUtils.hpp"
#include <cmath>

Cone::Cone(const Point3D &tip, const float &height, const Vector3D &direction, IMaterial *material, const float &angle)
: _tip(tip), _height(height), _direction(direction), _material(material), _angle(mathsUtils::degrees_to_radians(angle))
{
}

Cone::~Cone()
{
}

bool Cone::hits(const Ray &r, Interval ray_max, HitRecord &rec) const
{
    Vector3D oc = r.origin() - _tip;
    float a = r.direction()._x * r.direction()._x + r.direction()._z * r.direction()._z - powf(std::tan(_angle), 2) * r.direction()._y * r.direction()._y;
    float b = 2 * (oc._x * r.direction()._x + oc._z * r.direction()._z - powf(std::tan(_angle), 2) * oc._y * r.direction()._y);
    float c = oc._x * oc._x + oc._z * oc._z - powf(std::tan(_angle), 2) * oc._y * oc._y;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    float sqrt_d = std::sqrt(discriminant);

    float root = (-b - sqrt_d) / (2 * a);
    if (root < ray_max.min|| root > ray_max.max) {
        root = (-b + sqrt_d) / (2 * a);
        if (root < ray_max.min || root > ray_max.max)
            return false;
    }
    if ((r.at(root) - _tip).dot(_direction) <= 0)
        return false;

    Point3D temp_p = r.at(root);

    Point3D hitPoint = r.at(root);
    float height = _direction.dot(hitPoint - _tip);
    if (_height > 0 && (height < 0 || height > _height)) {
        return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - _tip).unit();
    rec.material = _material;

    return true;
}

void Cone::translate(const Point3D &trans)
{
    _tip += trans;
}

void Cone::rotate(const Point3D &degrees)
{
    (void)degrees;
}