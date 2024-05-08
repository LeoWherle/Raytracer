/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** WorldCreator
*/

#include "WorldCreator.hpp"

void WorldCreator::createWorld(World &world, const boost::property_tree::ptree &pt) const
{
    for (const auto &sphere : pt.get_child("spheres")) {
        world.addPrimitive(createSphere(sphere.second));
    }
    for (const auto &triangle : pt.get_child("triangles")) {
        world.addPrimitive(createTriangle(triangle.second));
    }
    for (const auto &plane : pt.get_child("planes")) {
        world.addPrimitive(createPlane(plane.second));
    }
    for (const auto &obj : pt.get_child("objects")) {
        world.addPrimitive(createObj(obj.second));
    }
}
