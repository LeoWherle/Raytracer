/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** SphereFactory
*/

#include <string>
#include <memory>
#include "SphereFactory.hpp"

std::unique_ptr<Sphere> SphereFactory::createSphere(const boost::property_tree::ptree &sphere) const
{
    auto center = createPoint3D(sphere.get_child("position"));
    auto radius = sphere.get<float>("radius");
    auto material = sphere.get<std::string>("material.material");

    IMaterial *mat = createMaterial(sphere.get_child("material"));

    return std::make_unique<Sphere>(center, radius, mat);
}
