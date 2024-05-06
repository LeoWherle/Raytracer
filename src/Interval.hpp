
#pragma once
#include <limits>

class Interval {
public:
    float min, max;

    Interval():
        min(+std::numeric_limits<float>::infinity()),
        max(-std::numeric_limits<float>::infinity())
    {
    } // Default interval is empty

    Interval(float min_, float max_):
        min(min_),
        max(max_)
    {
    }

    Interval(const Interval &a, const Interval &b)
    {
        // Create the interval tightly enclosing the two input intervals.
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }

    float size() const { return max - min; }

    bool contains(float x) const { return min <= x && x <= max; }

    bool surrounds(float x) const { return min < x && x < max; }

    float clamp(float x) const
    {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    Interval expand(float delta) const
    {
        auto padding = delta / 2;
        return Interval(min - padding, max + padding);
    }

    static const Interval empty, universe;
};

const Interval Interval::empty =
    Interval(+std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
const Interval Interval::universe =
    Interval(-std::numeric_limits<float>::infinity(), +std::numeric_limits<float>::infinity());

Interval operator+(const Interval &ival, float displacement)
{
    return Interval(ival.min + displacement, ival.max + displacement);
}

Interval operator+(float displacement, const Interval &ival) { return ival + displacement; }
