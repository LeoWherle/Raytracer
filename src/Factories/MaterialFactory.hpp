/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** MaterialFactory
*/

#pragma once

#include "Materials/IMaterial.hpp"
#include "Factories/ColorFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class MaterialFactory {
public:
    MaterialFactory() = default;
    ~MaterialFactory() = default;

    IMaterial *createMaterial(const boost::property_tree::ptree &pt) const;

private:
    ColorFactory _color_factory;
};
