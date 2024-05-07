/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PlaneFactory
*/

#include <string>
#include <memory>
#include "PlaneFactory.hpp"

std::shared_ptr<Plane> PlaneFactory::createPlane(const boost::property_tree::ptree &plane) const
{
    auto origin = _point3d_factory.createPoint3D(plane.get_child("position"));
    auto normal = _vector3d_factory.createVector3D(plane.get_child("normal"));
    auto material = plane.get<std::string>("material.material");

    IMaterial *mat = _material_factory.createMaterial(plane.get_child("material"));

    return std::make_shared<Plane>(origin, normal, mat);
}
