/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** TextureFactory
*/

#include "TextureFactory.hpp"

std::unique_ptr<ITexture> TextureFactory::createTexture(const boost::property_tree::ptree &pt) const
{
    std::string type = pt.get<std::string>("type");

    if (type == "color") {
        return createColorTexture(pt);
    } else if (type == "checker") {
        return createCheckerTexture(pt);
    }
    throw std::runtime_error("Unknown texture type: " + type);
}

std::unique_ptr<ITexture> TextureFactory::createCheckerTexture(const boost::property_tree::ptree &pt) const
{
    auto textodd = pt.get_child("oddTexture");
    auto texteven = pt.get_child("evenTexture");
    auto scale = pt.get<float>("scale");

    std::unique_ptr<ITexture> textureOdd;
    std::unique_ptr<ITexture> textureEven;

    if (textodd.get_child_optional("texture").is_initialized()) {
        textureOdd = createTexture(textodd.get_child("texture"));
    } else {
        textureOdd = createColorTexture(textodd);
    }

    if (texteven.get_child_optional("texture").is_initialized()) {
        textureEven = createTexture(texteven.get_child("texture"));
    } else {
        textureEven = createColorTexture(texteven);
    }


    return std::make_unique<CheckerTexture>(std::move(textureOdd), std::move(textureEven), scale);
}

std::unique_ptr<ITexture> TextureFactory::createColorTexture(const boost::property_tree::ptree &pt) const
{
    Color color = createColor(pt.get_child("color"));

    return std::make_unique<SolidColorTexture>(color);
}