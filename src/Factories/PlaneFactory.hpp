/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PlaneFactory
*/

#pragma once

#include "Primitives/Plane.hpp"
#include "Factories/Point3DFactory.hpp"
#include "Factories/Vector3DFactory.hpp"
#include "Factories/MaterialFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class PlaneFactory : public Point3DFactory, public Vector3DFactory, public MaterialFactory {
public:
    PlaneFactory() = default;
    ~PlaneFactory() = default;

    std::unique_ptr<Plane> createPlane(const boost::property_tree::ptree &pt) const;
};
