/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** TextureFactory
*/

#pragma once

#include <boost/property_tree/ptree.hpp>
#include <memory>

#include "ColorFactory.hpp"
#include "Textures/CheckerTexture.hpp"
#include "Textures/ITexture.hpp"
#include "Textures/SolidColorTexture.hpp"

class TextureFactory : public ColorFactory {
public:
    TextureFactory() = default;
    ~TextureFactory() = default;

    std::unique_ptr<ITexture> createTexture(const boost::property_tree::ptree &pt) const;
    std::unique_ptr<ITexture> createCheckerTexture(const boost::property_tree::ptree &pt) const;
    std::unique_ptr<ITexture> createColorTexture(const boost::property_tree::ptree &pt) const;

protected:
private:
};
