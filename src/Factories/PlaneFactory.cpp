/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PlaneFactory
*/

#include <string>
#include <memory>
#include "PlaneFactory.hpp"

std::unique_ptr<Plane> PlaneFactory::createPlane(const boost::property_tree::ptree &plane) const
{
    auto origin = createPoint3D(plane.get_child("position"));
    auto normal = createVector3D(plane.get_child("normal"));
    auto material = plane.get<std::string>("material.material");

    IMaterial *mat = createMaterial(plane.get_child("material"));

    return std::make_unique<Plane>(origin, normal, mat);
}
