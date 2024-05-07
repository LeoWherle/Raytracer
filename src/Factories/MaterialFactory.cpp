/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** MaterialFactory
*/

#include <string>
#include <memory>
#include "MaterialFactory.hpp"
#include "Materials/IMaterial.hpp"
#include "Materials/BaseMaterial.hpp"
#include "Materials/LightMaterial.hpp"
#include "Materials/MetalMaterial.hpp"

IMaterial *MaterialFactory::createMaterial(const boost::property_tree::ptree &pt) const
{
    std::string type = pt.get<std::string>("material");
    Color color = createColor(pt.get_child("color"));

    if (type == "BaseMaterial")
        return new BaseMaterial(color);
    if (type == "LightMaterial")
        return new LightMaterial(color);
    if (type == "MetalMaterial") {
        float fuzz = pt.get<float>("fuzz");
        return new MetalMaterial(color, fuzz);
    }
    return nullptr;
}
