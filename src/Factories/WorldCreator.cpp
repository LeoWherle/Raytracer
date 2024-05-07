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

    for (boost::property_tree::ptree::value_type sphere : pt.get_child("spheres")) {
        world.addPrimitive(_sphere_factory.createSphere(sphere.second));
    }
    for (boost::property_tree::ptree::value_type triangle : pt.get_child("triangles")) {
        world.addPrimitive(_triangle_factory.createTriangle(triangle.second));
    }
    for (boost::property_tree::ptree::value_type plane : pt.get_child("planes")) {
        world.addPrimitive(_plane_factory.createPlane(plane.second));
    }
    return world;
}