/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#pragma once

#include "IPrimitive.hpp"
#include "Math/MathsUtils.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"

class Cylinder : public IPrimitive {
    public:
        Point3D _origin;
        Vector3D _direction;
        double _radius;
        IMaterial *_material;

        inline Cylinder(const Point3D &origin, const Vector3D &direction, double radius, IMaterial *material):
            _origin(origin),
            _direction(direction),
            _radius(radius),
            _material(material)
        {
        }

        ~Cylinder() override = default;

        inline bool hits(const Ray& ray, Interval ray_max, HitRecord &rec) const override {
            float directdotD = _direction.dot(ray.direction());
            Vector3D Rl = ray.origin() - _origin;
            float directdotR = Rl.dot(_direction);

            float a = 1 - ((directdotD) * (directdotD));
            float b = 2 * ((Rl.dot(ray.direction())) - (directdotD * directdotR));
            float c = (Rl.dot(Rl)) - ((directdotR) * (directdotR)) - _radius * _radius;

            //Vector3D r_minus_c = ray.origin() - _origin;
            //float a = _direction.dot(_direction) * 2;
            //float b = _direction.dot(r_minus_c) * 4;
            //float c = r_minus_c.dot(r_minus_c) * 2 - _radius * _radius;

            float discriminant = b * b - 4 * a * c;
            if (discriminant < 0) {
                return false;
            }
            float t = (-b + sqrt(discriminant)) / (2.0 * a);
            if (t < 0) {
                //float t2 = (-b - sqrt(discriminant)) / (2.0 * a);
                //t = t < t2 ? t : t2;
                t = (-b - sqrt(discriminant)) / (2.0 * a);
            }
            if (t < 0 || !ray_max.surrounds(t)) {
                return false;
            }
            rec.t = t;
            rec.p = ray.at(t);
            auto cross = (rec.p - _origin).cross(_direction);
            auto norm = cross.cross(_direction);
            rec.normal = norm;
            rec.material = _material;
            return true;
        };

        inline void translate(const Point3D &trans) {
            _origin += trans;
        };

        inline void rotate(const Point3D &degrees) {
            float x = mathsUtils::degrees_to_radians(degrees._x);
            float y = mathsUtils::degrees_to_radians(degrees._y);
            float z = mathsUtils::degrees_to_radians(degrees._z);

            float mx[3][3] = {{1,0,0}, {0,cosf(x),-sinf(x)}, {0,sinf(x),cosf(x)}};
            float my[3][3] = {{cosf(y),0,sinf(y)}, {0,1,0}, {-sinf(y),0,cosf(y)}};
            float mz[3][3] = {{cosf(z),-sinf(z),0}, {sinf(z),cosf(z),0}, {0,0,1}};

            _direction = Vector3D(mx[0][0] * _direction._x + mx[0][1] * _direction._y + mx[0][2] * _direction._z,
                mx[1][0] * _direction._x + mx[1][1] * _direction._y + mx[1][2] * _direction._z,
                mx[2][0] * _direction._x + mx[2][1] * _direction._y + mx[2][2] * _direction._z);
            _direction = Vector3D(my[0][0] * _direction._x + my[0][1] * _direction._y + my[0][2] * _direction._z,
                my[1][0] * _direction._x + my[1][1] * _direction._y + my[1][2] * _direction._z,
                my[2][0] * _direction._x + my[2][1] * _direction._y + my[2][2] * _direction._z);
            _direction = Vector3D(mz[0][0] * _direction._x + mz[0][1] * _direction._y + mz[0][2] * _direction._z,
                mz[1][0] * _direction._x + mz[1][1] * _direction._y + mz[1][2] * _direction._z,
                mz[2][0] * _direction._x + mz[2][1] * _direction._y + mz[2][2] * _direction._z);
        };
};
