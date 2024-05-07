/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ColorFactory
*/

#pragma once

#include "Color.hpp"
#include <boost/property_tree/ptree.hpp>

class ColorFactory {
public:
    ColorFactory() = default;
    ~ColorFactory() = default;

    Color createColor(const boost::property_tree::ptree &pt) const;
};
