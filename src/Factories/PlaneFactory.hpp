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

class PlaneFactory {
public:
    PlaneFactory() = default;
    ~PlaneFactory() = default;

    std::shared_ptr<Plane> createPlane(const boost::property_tree::ptree &pt) const;

private:
    MaterialFactory _material_factory;
    Point3DFactory _point3d_factory;
    Vector3DFactory _vector3d_factory;
};
