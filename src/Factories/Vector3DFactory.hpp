/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Vector3DFactory
*/

#pragma once

#include "Math/Vector3D.hpp"
#include <boost/property_tree/ptree.hpp>

class Vector3DFactory {
public:
    Vector3DFactory() = default;
    ~Vector3DFactory() = default;

    Vector3D createVector3D(const boost::property_tree::ptree &pt) const;
};
