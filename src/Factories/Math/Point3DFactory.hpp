/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Point3DFactory
*/

#pragma once

#include "Math/Point3D.hpp"
#include <boost/property_tree/ptree.hpp>

class Point3DFactory {
public:
    Point3DFactory() = default;
    ~Point3DFactory() = default;

    Point3D createPoint3D(const boost::property_tree::ptree &pt) const;
};
