/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Image
*/

#include "Image.hpp"

void Image::resize(uint32_t width, uint32_t height)
{
    if (width == _width && height == _height) {
        return;
    }
    _width = width;
    _height = height;
    _pixels.resize(width * height * 4);
    for (size_t i = 0; i < _pixels.size(); i += 4) {
        _pixels[i + 3] = 255;
    }
}

void Image::set_pixel(uint32_t x, uint32_t y, Color pixel_color, uint32_t, float)
{
    auto color = pixel_color.to_gamma().clamp();
    auto index = (x + y * _width) * 4;
    _pixels[index] = color.getR();
    _pixels[index + 1] = color.getG();
    _pixels[index + 2] = color.getB();
}

Color Image::get_pixel(uint32_t x, uint32_t y) const
{
    auto index = (x + y * _width) * 4;
    return Color(_pixels[index], _pixels[index + 1], _pixels[index + 2]);
}

void Image::writePixelInPPM(std::ofstream &out, uint32_t i, uint32_t j) const
{
    out << static_cast<uint32_t>(_pixels[(j * _width + i) * 4 + 0]) << ' '
        << static_cast<uint32_t>(_pixels[(j * _width + i) * 4 + 1]) << ' '
        << static_cast<uint32_t>(_pixels[(j * _width + i) * 4 + 2]) << '\n';
}

auto Image::get_stream() -> uint8_t *
{
    return _pixels.data();
}

uint32_t Image::get_width() const
{
    return _width;
}

uint32_t Image::get_height() const
{
    return _height;
}

void Image::writePPM(const std::string &filename) const
{
    std::ofstream out(filename);
    out << "P3\n" << _width << ' ' << _height << "\n255\n";
    for (uint32_t j = 0; j < _height; j++) {
        for (uint32_t i = 0; i < _width; i++) {
            writePixelInPPM(out, i, j);
        }
    }
}

void Image::writeBMP(const std::string &filename) const
{
    std::ofstream out(filename, std::ios::binary);
    BMPHeader header;
    header.fileSize = 54 + 3 * _width * _height;
    header.width = _width;
    header.height = _height;
    header.imageSize = 3 * _width * _height;
    out.write(reinterpret_cast<char *>(&header), sizeof(header));
    for (uint32_t j = _height; j != 0; j--) {
        for (uint32_t i = 0; i < _width; i++) {
            out.put(_pixels[((j - 1) * _width + i) * 4 + 2]);
            out.put(_pixels[((j - 1) * _width + i) * 4 + 1]);
            out.put(_pixels[((j - 1) * _width + i) * 4 + 0]);
        }
    }
}

void Image::writePNG(const std::string &filename) const
{
    sf::Image image;
    image.create(_width, _height, _pixels.data());
    image.saveToFile(filename);
}

void Image::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Texture texture;
    texture.create(_width, _height);
    texture.update(_pixels.data());
    target.draw(sf::Sprite(texture), states);
}

void Image::clear(void)
{
    for (size_t i = 0; i < _pixels.size(); i += 4) {
        _pixels[i] = 0;
        _pixels[i + 1] = 0;
        _pixels[i + 2] = 0;
    }
}