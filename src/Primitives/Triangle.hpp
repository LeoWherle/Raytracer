/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Triangle
*/

#pragma once

#include <memory>
#include <array>

#include "IPrimitive.hpp"
#include "Materials/IMaterial.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

class Triangle : public IPrimitive {
    private:
        // Vertices of the triangle
        Point3D _v0;
        Point3D _v1;
        Point3D _v2
        Vector3D _normal;
        std::shared_ptr<IMaterial> _material;
    public:
        Triangle(const Point3D &v0, const Point3D &v1, const Point3D &v2, std::shared_ptr<IMaterial> mat):
            _v0(v0),
            _v1(v1),
            _v2(v2),
            _material(mat)
        {
            _normal = (v1 - v0).cross(v2 - v0).normalize();
        }
        ~Triangle() = default;

        bool hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const override
        {
            // Möller-Trumbore intersection algorithm
            // https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
            const float EPSILON = 0.0000001;
            Vector3D edge1 = _v1 - _v0;
            Vector3D edge2 = _v2 - _v0;

            Vector3D pvec = ray.direction().cross(edge2);
            float det = edge1.dot(pvec);

            if (det > -EPSILON && det < EPSILON)
                return false;

            float inv_det = 1.0 / det;
            Vector3D tvec = ray.origin() - _v0;
            float u = inv_det * tvec.dot(pvec);

            if (u < 0.0 || u > 1.0)
                return false;

            Vector3D qvec = tvec.cross(edge1);
            float v = inv_det * ray.direction().dot(qvec);

            if (v < 0.0 || u + v > 1.0)
                return false;

            float t = inv_det * edge2.dot(qvec);
            if (t > EPSILON) {
                hitrec.t = t;
                hitrec.p = ray.at(t);
                hitrec.normal = _normal;
                hitrec.material = _material;
                return true;
            }
            return false;
        }

    protected:
    private:
};
