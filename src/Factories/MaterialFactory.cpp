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

const IMaterial *MaterialFactory::createMaterial(const boost::property_tree::ptree &pt) const
{
    std::string type = pt.get<std::string>("material");

    std::unique_ptr<ITexture> texture;

    if (pt.get_child_optional("texture").is_initialized()) {
        texture = createTexture(pt.get_child("texture"));
    } else {
        texture = createColorTexture(pt);
    }

    if (type == "BaseMaterial")
        return new BaseMaterial(std::move(texture));
    if (type == "LightMaterial")
        return new LightMaterial(std::move(texture));
    if (type == "MetalMaterial") {
        float fuzz = pt.get<float>("fuzz");
        return new MetalMaterial(std::move(texture), fuzz);
    }
    return nullptr;
}
