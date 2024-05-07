/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** World
*/

#include "World.hpp"

void World::addPrimitive(std::shared_ptr<IPrimitive> primitive)
{
    primitives.push_back(std::move(primitive));
}

bool World::hits(const Ray &r, Interval ray_d, HitRecord &rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_d.max;
    for (const auto &object : primitives) {
        if (object->hits(r, Interval(ray_d.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
