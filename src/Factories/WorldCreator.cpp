/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** WorldCreator
*/

#include "WorldCreator.hpp"

void WorldCreator::createWorld(World &world, const boost::property_tree::ptree &pt) const
{
    boost::property_tree::ptree primitives = pt.get_child("primitives");
    JsonLoader jsonLoader;

    for (const auto &scene : pt.get_child("scenes")) {
        jsonLoader.load(scene.second.get<std::string>("path"));
        createWorld(world, jsonLoader.json);
    }

    for (const auto &sphere : primitives.get_child("spheres")) {
        world.addPrimitive(createSphere(sphere.second));
    }
    for (const auto &triangle : primitives.get_child("triangles")) {
        world.addPrimitive(createTriangle(triangle.second));
    }
    for (const auto &plane : primitives.get_child("planes")) {
        world.addPrimitive(createPlane(plane.second));
    }
    for (const auto &obj : primitives.get_child("objects")) {
        world.addPrimitive(createObj(obj.second));
    }
    for (const auto &obj : primitives.get_child("cones")) {
        world.addPrimitive(createCone(obj.second));
    }
    for (const auto &cylinder : primitives.get_child("cylinders")) {
        world.addPrimitive(createCylinder(cylinder.second));
    }
}
