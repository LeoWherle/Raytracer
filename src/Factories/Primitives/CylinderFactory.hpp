/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** CylinderFactory
*/

#pragma once

#include "Primitives/Cylinder.hpp"
#include "Factories/Math/Point3DFactory.hpp"
#include "Factories/Math/Vector3DFactory.hpp"
#include "Factories/MaterialFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class CylinderFactory : public Point3DFactory, public Vector3DFactory, public MaterialFactory {
    public:
        CylinderFactory() = default;
        ~CylinderFactory() = default;

        std::unique_ptr<Cylinder> createCylinder(const boost::property_tree::ptree &pt) const;
};
