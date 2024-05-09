/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Triangle
*/

#include "TriangleObj.hpp"

bool TriangleObj::hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const
{
    Vector3D edge1 = _vertices[1] - _vertices[0];
    Vector3D edge2 = _vertices[2] - _vertices[0];

    Vector3D pvec = ray.direction().cross(edge2);
    float det = edge1.dot(pvec);
    if (det > -0.00001 && det < 0.00001)
        return false;

    float inv_det = static_cast<float>(1.0 / det);
    Vector3D tvec = ray.origin() - _vertices[0];
    float u = inv_det * tvec.dot(pvec);
    if (u < 0.0 || u > 1.0)
        return false;

    Vector3D qvec = tvec.cross(edge1);
    float v = inv_det * ray.direction().dot(qvec);
    if (v < 0.0 || u + v > 1.0)
        return false;

    float t = inv_det * edge2.dot(qvec);
    if (t > 0.00001 && ray_d.surrounds(t)) {
        auto normal = _normals[0] * (1 - u - v) + _normals[1] * u + _normals[2] * v;
        hitrec.t = t;
        hitrec.p = ray.at(t);
        hitrec.normal = normal;
        hitrec.material = _material;
        return true;
    }
    return false;
}