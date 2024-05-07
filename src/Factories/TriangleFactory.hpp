/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** TriangleFactory
*/

#pragma once

#include "Primitives/Triangle.hpp"
#include "Factories/Point3DFactory.hpp"
#include "Factories/MaterialFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class TriangleFactory {
public:
    TriangleFactory() = default;
    ~TriangleFactory() = default;

    std::shared_ptr<Triangle> createTriangle(const boost::property_tree::ptree &pt) const;

private:
    MaterialFactory _material_factory;
    Point3DFactory _point3d_factory;
};
