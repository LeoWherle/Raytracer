/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Image
*/

#pragma once

#include "Color.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <omp.h>
#include <vector>

#include <iostream>

class Image {
public:
    Image() = default;
    Image(uint32_t width, uint32_t height):
        _width(width),
        _height(height)
    {
        _pixels.resize(width * height * 4);
    }
    ~Image() = default;

protected:
private:
public:
    void resize(uint32_t width, uint32_t height)
    {
        if (width == _width && height == _height) {
            return;
        }
        _width = width;
        _height = height;
        _pixels.resize(width * height * 4);
    }

    void set_pixel(uint32_t x, uint32_t y, Color pixel_color)
    {
        auto color = pixel_color.to_gamma().clamp();
        auto index = (x + y * _width) * 4;
        _pixels[index] = color.getR();
        _pixels[index + 1] = color.getG();
        _pixels[index + 2] = color.getB();
    }

private:
    void writePixelInPPM(std::ofstream &out, uint32_t i, uint32_t j)
    {
        out << static_cast<uint32_t>(_pixels[(j * _width + i) * 4 + 0]) << ' '
            << static_cast<uint32_t>(_pixels[(j * _width + i) * 4 + 1]) << ' '
            << static_cast<uint32_t>(_pixels[(j * _width + i) * 4 + 2]) << '\n';
    }

public:
    auto get_stream() -> sf::Uint8 * { return _pixels.data(); }

public:
    void writePPM(const std::string &filename)
    {
        std::ofstream out(filename);
        out << "P3\n" << _width << ' ' << _height << "\n255\n";
        for (uint32_t j = 0; j < _height; j++) {
            for (uint32_t i = 0; i < _width; i++) {
                writePixelInPPM(out, i, j);
            }
        }
    }

#pragma pack(push, 1)
    struct BMPHeader {
        char signature[2] = {'B', 'M'};
        uint32_t fileSize;
        uint32_t reserved = 0;
        uint32_t dataOffset = 54;
        uint32_t headerSize = 40;
        int32_t width;
        int32_t height;
        uint16_t planes = 1;
        uint16_t bitsPerPixel = 24;
        uint32_t compression = 0;
        uint32_t imageSize;
        int32_t xPixelsPerMeter = 0;
        int32_t yPixelsPerMeter = 0;
        uint32_t totalColors = 0;
        uint32_t importantColors = 0;
    };
#pragma pack(pop)

    /**
     * @brief https://en.wikipedia.org/wiki/BMP_file_format
     * @param filename the name of the file to write
     */
    void writeBMP(const std::string &filename)
    {
        std::ofstream out(filename, std::ios::binary);
        BMPHeader header;
        header.fileSize = 54 + 3 * _width * _height;
        header.width = _width;
        header.height = _height;
        header.imageSize = 3 * _width * _height;
        out.write(reinterpret_cast<char *>(&header), sizeof(header));
        for (uint32_t j = _height; j > 0; j--) {
            for (uint32_t i = 0; i < _width; i++) {
                out.write((char *) &_pixels[(j * _width + i) * 4 + 2], 1);
                out.write((char *) &_pixels[(j * _width + i) * 4 + 1], 1);
                out.write((char *) &_pixels[(j * _width + i) * 4 + 0], 1);
            }
        }
    }

    void writePNG(const std::string &filename)
    {
        sf::Image image;
        for (size_t i = 0; i < _pixels.size(); i += 4) {
            _pixels[i + 3] = 255;
        }
        image.create(_width, _height, _pixels.data());
        image.saveToFile(filename);
    }

protected:
private:
    std::vector<sf::Uint8> _pixels;
    uint32_t _width;
    uint32_t _height;
};
