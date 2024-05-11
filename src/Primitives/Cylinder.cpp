/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

bool Cylinder::hits(const Ray &ray, Interval ray_max, HitRecord &rec) const
{
    Vector3D oc = ray.origin() - _origin;
    float a = ray.direction().dot(ray.direction()) -
        _direction.dot(ray.direction()) * _direction.dot(ray.direction());
    float b = 2 * (ray.direction().dot(oc) - _direction.dot(ray.direction()) * _direction.dot(oc));
    float c = oc.dot(oc) - _direction.dot(oc) * _direction.dot(oc) - _radius * _radius;
    
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }

    float disc_sqrt = std::sqrt(discriminant);

    float root = (-b - disc_sqrt) / (2 * a);
    if (!ray_max.surrounds(root)) {
        root = (-b + disc_sqrt) / (2 * a);
        if (!ray_max.surrounds(root)) {
            return false;
        }
    }
    Point3D hitPoint = ray.at(root);
    float height = _direction.dot(hitPoint - _origin);
    if (_height > 0 && (height < 0 || height > _height)) {
        return false;
    }
    rec.t = root;
    rec.p = hitPoint;
    rec.normal = (rec.p - _origin - _direction * _direction.dot(rec.p - _origin)).unit();
    rec.material = _material;
    return true;
};

void Cylinder::translate(const Point3D &trans) { _origin += trans; };

void Cylinder::rotate(const Point3D &degrees)
{
    float x = mathsUtils::degrees_to_radians(degrees._x);
    float y = mathsUtils::degrees_to_radians(degrees._y);
    float z = mathsUtils::degrees_to_radians(degrees._z);

    float mx[3][3] = {{1, 0, 0}, {0, cosf(x), -sinf(x)}, {0, sinf(x), cosf(x)}};
    float my[3][3] = {{cosf(y), 0, sinf(y)}, {0, 1, 0}, {-sinf(y), 0, cosf(y)}};
    float mz[3][3] = {{cosf(z), -sinf(z), 0}, {sinf(z), cosf(z), 0}, {0, 0, 1}};

    _direction = Vector3D(
        mx[0][0] * _direction._x + mx[0][1] * _direction._y + mx[0][2] * _direction._z,
        mx[1][0] * _direction._x + mx[1][1] * _direction._y + mx[1][2] * _direction._z,
        mx[2][0] * _direction._x + mx[2][1] * _direction._y + mx[2][2] * _direction._z
    );
    _direction = Vector3D(
        my[0][0] * _direction._x + my[0][1] * _direction._y + my[0][2] * _direction._z,
        my[1][0] * _direction._x + my[1][1] * _direction._y + my[1][2] * _direction._z,
        my[2][0] * _direction._x + my[2][1] * _direction._y + my[2][2] * _direction._z
    );
    _direction = Vector3D(
        mz[0][0] * _direction._x + mz[0][1] * _direction._y + mz[0][2] * _direction._z,
        mz[1][0] * _direction._x + mz[1][1] * _direction._y + mz[1][2] * _direction._z,
        mz[2][0] * _direction._x + mz[2][1] * _direction._y + mz[2][2] * _direction._z
    );
};