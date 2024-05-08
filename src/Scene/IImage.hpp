#pragma once

#include <cstdint>
#include <iterator>

#include "Color.hpp"

class IImage {
public:
    ~IImage() = default;
    virtual void resize(uint32_t width, uint32_t height) = 0;

    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_height() const = 0;

    virtual void set_pixel(uint32_t x, uint32_t y, Color pixel_color, uint32_t weight, float width) = 0;
    virtual Color get_pixel(uint32_t x, uint32_t y) const = 0;

    virtual void finish_frame(uint32_t weight, float depth)
    {
        (void) weight;
        (void) depth;
    }
    virtual uint32_t get_sample_count() const { return 0; }

    virtual void clear() = 0;

protected:
private:
};
