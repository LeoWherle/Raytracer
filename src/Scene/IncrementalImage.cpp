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
    (void) depth;
    auto index = (x + y * _image.get_width());
    auto &pixel = _pixels[index];
    float p_weight = static_cast<float>(_weight);
    float n_weight = static_cast<float>(weight);
    pixel = (pixel * p_weight + pixel_color * n_weight) / (p_weight + n_weight);
    _image.set_pixel(x, y, pixel);
}

void IncrementalImage::finish_frame(uint32_t weight, float depth)
{
    _weight += weight;
    _depth = (_depth * static_cast<float>(_weight) + depth) / static_cast<float>(_weight + 1);
}

Color IncrementalImage::get_pixel(uint32_t x, uint32_t y) const { return _image.get_pixel(x, y); }

uint32_t IncrementalImage::get_width() const { return _image.get_width(); }

uint32_t IncrementalImage::get_height() const { return _image.get_height(); }

uint32_t IncrementalImage::get_sample_count() const { return _weight; }

void IncrementalImage::clear()
{
    _image.clear();
    _pixels.clear();
    _weight = 0;
    _depth = 0;
}

void IncrementalImage::save(const std::string &filename) const { _image.save(filename); }
