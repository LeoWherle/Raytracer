
#pragma once
#include <limits>

class Interval {
public:
    double min, max;

    Interval():
        min(+std::numeric_limits<double>::infinity()),
        max(-std::numeric_limits<double>::infinity())
    {
    } // Default interval is empty

    Interval(double min_, double max_):
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

    double size() const { return max - min; }

    bool contains(double x) const { return min <= x && x <= max; }

    bool surrounds(double x) const { return min < x && x < max; }

    double clamp(double x) const
    {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    Interval expand(double delta) const
    {
        auto padding = delta / 2;
        return Interval(min - padding, max + padding);
    }

    static const Interval empty, universe;
};

const Interval Interval::empty =
    Interval(+std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
const Interval Interval::universe =
    Interval(-std::numeric_limits<double>::infinity(), +std::numeric_limits<double>::infinity());

Interval operator+(const Interval &ival, double displacement)
{
    return Interval(ival.min + displacement, ival.max + displacement);
}

Interval operator+(double displacement, const Interval &ival) { return ival + displacement; }
