/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Image
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Image {
public:
    Image() = default;
    Image(int width, int height):
        _width(width),
        _height(height)
    {
        _pixels.resize(width * height * 4);
    }
    ~Image() = default;

protected:
private:
public:
    void resize(int width, int height)
    {
        if (width == _width && height == _height) {
            return;
        }
        _width = width;
        _height = height;
        _pixels.resize(width * height * 4);
    }

    void set_pixel(int x, int y, Color pixel_color)
    {
        auto color = pixel_color.to_gamma().clamp(256);
        auto index = (x + y * _width) * 4;
        _pixels[index] = color.getR();
        _pixels[index + 1] = color.getG();
        _pixels[index + 2] = color.getB();
    }

private:
    void writePixelInPPM(std::ofstream &out, uint32_t i, uint32_t j)
    {
        out << static_cast<int>(_pixels[(j * _width + i) * 4 + 0]) << ' '
            << static_cast<int>(_pixels[(j * _width + i) * 4 + 1]) << ' '
            << static_cast<int>(_pixels[(j * _width + i) * 4 + 2]) << '\n';
    }

public:

    auto get_stream() -> sf::Uint8 * { return _pixels.data(); }

public:
    void writePPM(const std::string &filename)
    {
        std::ofstream out(filename);
        out << "P3\n" << _width << ' ' << _height << "\n255\n";
        for (int j = 0; j < _height; j++) {
            for (int i = 0; i < _width; i++) {
                writePixelInPPM(out, i, j);
            }
        }
    }

    void writePNG(const std::string &filename)
    {
        sf::Image image;
        image.create(_width, _height, _pixels.data());
        image.saveToFile(filename);
    }


protected:
private:
    std::vector<sf::Uint8> _pixels;
    int _width;
    int _height;
};
