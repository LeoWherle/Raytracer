/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** IncrementalImage
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>

#include "IImage.hpp"
#include "Image.hpp"
#include "Color.hpp"

class IncrementalImage : public sf::Drawable, public IImage {
public:
    struct Pixel {
        Color color; // Linear color
        uint32_t weight; // number of samples
        float depth; // average number of depth per sample
    };
    IncrementalImage() = default;
    ~IncrementalImage() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        _image.draw(target, states);
    }

    void resize(uint32_t width, uint32_t height)
    {
        _image.resize(width, height);
        _pixels.resize(width * height);
    }

    void set_pixel(uint32_t x, uint32_t y, Color pixel_color, uint32_t weight = 1, float depth = 1)
    {
        auto index = (x + y * _image.get_width());
        auto &pixel = _pixels[index];
        float p_weight = static_cast<float>(pixel.weight);
        float n_weight = static_cast<float>(weight);
        pixel.color = (pixel.color * p_weight + pixel_color * n_weight) / (p_weight + n_weight);
        pixel.weight += weight;
        pixel.depth = (pixel.depth * p_weight + depth) / (p_weight + 1);
        _image.set_pixel(x, y, pixel.color, pixel.weight, pixel.depth);
    }

    Color get_pixel(uint32_t x, uint32_t y) const
    {
        return _image.get_pixel(x, y);
    }

    uint32_t get_width() const
    {
        return _image.get_width();
    }

    uint32_t get_height() const
    {
        return _image.get_height();
    }

    void clear()
    {
        _image.clear();
        _pixels.clear();
    }

protected:
private:
    Image _image;
    std::vector<Pixel> _pixels;
};
