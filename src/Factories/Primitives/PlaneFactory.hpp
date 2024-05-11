/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PlaneFactory
*/

#pragma once

#include "Primitives/Plane.hpp"
#include "Factories/Math/Point3DFactory.hpp"
#include "Factories/Math/Vector3DFactory.hpp"
#include "Factories/MaterialFactory.hpp"
#include <list>
#include <boost/property_tree/ptree.hpp>

class PlaneFactory : public Point3DFactory, public Vector3DFactory, public MaterialFactory {
public:
    PlaneFactory() = default;
    ~PlaneFactory() = default;

    std::unique_ptr<Plane> createPlane(const boost::property_tree::ptree &pt) const;

private:
    const std::list<std::string> valid_transformations = {
        "translation",
        "rotation"
    };
};
