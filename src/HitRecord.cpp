/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** HitRecord
*/

#include "HitRecord.hpp"

void HitRecord::set_face_normal(const Ray &ray, const Vector3D &out_normal)
{
    front_face = out_normal.dot(ray.direction()) < 0;
    normal = front_face ? out_normal : -out_normal;
}
