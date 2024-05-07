/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** WorldCreator
*/

#pragma once

#include "../Scene/World.hpp"
#include "Factories/SphereFactory.hpp"
#include "Factories/TriangleFactory.hpp"
#include "Factories/PlaneFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class WorldCreator {
public:
    WorldCreator() = default;
    ~WorldCreator() = default;

    World createWorld(const boost::property_tree::ptree &pt) const;

private:
    SphereFactory _sphere_factory;
    TriangleFactory _triangle_factory;
    PlaneFactory _plane_factory;
};
