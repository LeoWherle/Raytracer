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

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void resize(uint32_t width, uint32_t height);

    void set_pixel(uint32_t x, uint32_t y, Color pixel_color, uint32_t weight = 1, float depth = 1);

    Color get_pixel(uint32_t x, uint32_t y) const;

    uint32_t get_width() const;

    uint32_t get_height() const;

    void clear();

protected:
private:
    Image _image;
    std::vector<Pixel> _pixels;
};
