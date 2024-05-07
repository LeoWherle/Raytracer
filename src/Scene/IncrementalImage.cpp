/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** IncrementalImage
*/

#include "IncrementalImage.hpp"

void IncrementalImage::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    _image.draw(target, states);
}

void IncrementalImage::resize(uint32_t width, uint32_t height)
{
    _image.resize(width, height);
    _pixels.resize(width * height);
}

void IncrementalImage::set_pixel(uint32_t x, uint32_t y, Color pixel_color, uint32_t weight, float depth)
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

Color IncrementalImage::get_pixel(uint32_t x, uint32_t y) const
{
    return _image.get_pixel(x, y);
}

uint32_t IncrementalImage::get_width() const
{
    return _image.get_width();
}

uint32_t IncrementalImage::get_height() const
{
    return _image.get_height();
}

void IncrementalImage::clear()
{
    _image.clear();
    _pixels.clear();
}
