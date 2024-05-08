/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** SphereFactory
*/

#pragma once

#include "Primitives/Sphere.hpp"
#include "Factories/Math/Point3DFactory.hpp"
#include "Factories/MaterialFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class SphereFactory : public Point3DFactory, public MaterialFactory {
public:
    SphereFactory() = default;
    ~SphereFactory() = default;

    std::unique_ptr<Sphere> createSphere(const boost::property_tree::ptree &pt) const;
};
