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

class WorldCreator : public SphereFactory, public TriangleFactory, public PlaneFactory {
public:
    WorldCreator() = default;
    ~WorldCreator() = default;

    void createWorld(World &world, const boost::property_tree::ptree &pt) const;
};
