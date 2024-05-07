/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** WorldCreator
*/

#include "WorldCreator.hpp"

World WorldCreator::createWorld(const boost::property_tree::ptree &pt) const
{
    World world;

    for (const auto &sphere : pt.get_child("spheres")) {
        world.addPrimitive(createSphere(sphere.second));
    }
    for (const auto &triangle : pt.get_child("triangles")) {
        world.addPrimitive(createTriangle(triangle.second));
    }
    for (const auto &plane : pt.get_child("planes")) {
        world.addPrimitive(createPlane(plane.second));
    }
    return world;
}