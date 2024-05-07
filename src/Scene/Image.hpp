/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Image
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#include "Color.hpp"
#include "IImage.hpp"

class Image : public sf::Drawable, public IImage {
public:
    Image() = default;
    Image(uint32_t width, uint32_t height):
        _width(width),
        _height(height)
    {
        _pixels.resize(width * height * 4);
        for (size_t i = 0; i < _pixels.size(); i += 4) {
            _pixels[i + 3] = 255;
        }
    }
    ~Image() = default;

    void resize(uint32_t width, uint32_t height);

    void set_pixel(uint32_t x, uint32_t y, Color pixel_color, uint32_t, float);

    Color get_pixel(uint32_t x, uint32_t y) const;

private:
    void writePixelInPPM(std::ofstream &out, uint32_t i, uint32_t j) const;

public:
    auto get_stream() -> uint8_t *;

    uint32_t get_width() const;
    uint32_t get_height() const;

public:
    void writePPM(const std::string &filename) const;

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
    void writeBMP(const std::string &filename) const;

    void writePNG(const std::string &filename) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void clear(void);

protected:
private:
    std::vector<uint8_t> _pixels;
    uint32_t _width;
    uint32_t _height;
};
