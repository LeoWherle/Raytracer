/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** WorldCreator
*/

#pragma once

#include "Scene/World.hpp"
#include "Primitives/SphereFactory.hpp"
#include "Primitives/TriangleFactory.hpp"
#include "Primitives/ObjFactory.hpp"
#include "Primitives/PlaneFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class WorldCreator : public SphereFactory, public TriangleFactory, public PlaneFactory, public ObjFactory {
public:
    WorldCreator() = default;
    ~WorldCreator() = default;

    void createWorld(World &world, const boost::property_tree::ptree &pt) const;
};
