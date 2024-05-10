/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** Cone
*/

#include "Cone.hpp"
#include "Math/MathsUtils.hpp"
#include <cmath>

Cone::Cone(const Point3D &tip, const Vector3D &height, const Vector3D &direction, IMaterial *material, const float &angle)
: _tip(tip), _height(height), _direction(direction), _material(material), _angle(mathsUtils::degrees_to_radians(angle))
{
}

Cone::~Cone()
{
}

bool Cone::hits(const Ray &r, Interval ray_max, HitRecord &rec) const
{
    float half_angle = _angle / 2;
    float cosa = powf(cosf(half_angle), 2);

    float DD = r.direction().dot(_direction);
    Vector3D CO = (r.origin() - _tip);
    float DR = CO.dot(_direction);

    float a = powf(DD, 2) - cosa;
    float b = 2 * (DD * DR - r.direction().dot(CO) * cosa);
    float c = powf(DR, 2) - CO.dot(CO) * cosa;

    float det = powf(b, 2) - 4 * a * c;

    if (det < 0) {
        return false;
    }

    float sqrtd = std::sqrt(det);

    float root = (b - sqrtd) / (2 * a);
    if (!ray_max.surrounds(root)) {
        root = (b + sqrtd) / (2 * a);
        if (!ray_max.surrounds(root))
            return false;
    }

    Point3D P = r.at(root);        // intersection point equation P = O + d*t
    Vector3D PC = (P - _tip);      // vector from cone apex to intersection point

    if (PC.dot(_direction) > 0) {
        return false;
    }

    rec.t = root;     // intersection point according to space
    rec.p = P;        // intersection point translated

    // P is the vertex of the cone
    // I is the intersection point
    // Сame up with simpler method:
    // Find distance Dis from intersection point I to base P
    // Make axis orientation vector of length

    // D = Dis * sqrt(1+k^2)
    // and make point on axis at this distance

    // A = P + Normalized(Orient) * D
    // Now

    // Normal = I - A
    auto D = PC * sqrtf(1 + powf(tanf(half_angle), 2));
    auto A = _tip + _direction.unit() * D;

    auto outward_normal = rec.p - A;

    rec.set_face_normal(r, outward_normal);
    rec.material = _material;
    return true;
}

void Cone::translate(const Point3D &trans)
{
    _tip += trans;
    _height += Vector3D(trans._x, trans._y, trans._z);
}

void Cone::rotate(const Point3D &degrees)
{
    (void)degrees;
}