/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** CheckerTexture
*/

#pragma once

#include "Color.hpp"
#include "ITexture.hpp"
#include "SolidColorTexture.hpp"
#include <cmath>
#include <memory>

class CheckerTexture : public ITexture {
    std::unique_ptr<ITexture> _textureOdd;
    std::unique_ptr<ITexture> _textureEven;

    float _scale;

public:
    CheckerTexture(const Color &c1, const Color &c2, float scale = 1.0f):
        _textureOdd(std::make_unique<SolidColorTexture>(c1)),
        _textureEven(std::make_unique<SolidColorTexture>(c2)),
        _scale(1.0f / scale)
    {
    }

    CheckerTexture(std::unique_ptr<ITexture> t1, std::unique_ptr<ITexture> t2, float scale = 1.0f):
        _textureOdd(std::move(t1)),
        _textureEven(std::move(t2)),
        _scale(1.0f / scale)
    {
    }

    ~CheckerTexture() = default;

    Color value(float u, float v, const Point3D &p) const override
    {

        auto xInteger = static_cast<int>(std::floor(_scale * p._x));
        auto yInteger = static_cast<int>(std::floor(_scale * p._y));
        auto zInteger = static_cast<int>(std::floor(_scale * p._z));

        bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

        if (isEven) {
            return _textureOdd->value(u, v, p);
        } else {
            return _textureEven->value(u, v, p);
        }
    }

protected:
private:
};
