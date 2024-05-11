/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** IncrementalImage
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <tuple>
#include <vector>

#include "Color.hpp"
#include "IImage.hpp"
#include "ISaveable.hpp"
#include "Image.hpp"

class IncrementalImage : public sf::Drawable, public IImage, public ISaveable {
public:
    IncrementalImage() = default;
    ~IncrementalImage() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void resize(uint32_t width, uint32_t height);

    void set_pixel(uint32_t x, uint32_t y, Color pixel_color, uint32_t weight = 1, float depth = 1);
    void finish_frame(uint32_t weight, float depth);

    Color get_pixel(uint32_t x, uint32_t y) const;

    uint32_t get_width() const;

    uint32_t get_height() const;

    uint32_t get_sample_count() const;

    void clear();

    void save(const std::string &filename) const override;

protected:
private:
    uint32_t _weight = 1; // number of samples
    float _depth; // average number of depth per sample
    Image _image;
    std::vector<Color> _pixels;
};
