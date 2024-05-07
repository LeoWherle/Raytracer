/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** SphereFactory
*/

#pragma once

#include "Primitives/Sphere.hpp"
#include "Factories/Point3DFactory.hpp"
#include "Factories/MaterialFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class SphereFactory {
public:
    SphereFactory() = default;
    ~SphereFactory() = default;

    std::unique_ptr<Sphere> createSphere(const boost::property_tree::ptree &pt) const;

private:
    MaterialFactory _material_factory;
    Point3DFactory _point3d_factory;
};
