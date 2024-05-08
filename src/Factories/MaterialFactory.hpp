/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** MaterialFactory
*/

#pragma once

#include "Materials/IMaterial.hpp"
#include "Factories/TextureFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class MaterialFactory : public TextureFactory {
public:
    MaterialFactory() = default;
    ~MaterialFactory() = default;

    IMaterial *createMaterial(const boost::property_tree::ptree &pt) const;

};
