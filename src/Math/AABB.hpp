/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** AABB
*/

#pragma once

#include "Math/Interval.hpp"
#include "Point3D.hpp"
#include "Primitives/IPrimitive.hpp"

class AABB {
public:
    Point3D m_min;
    Point3D m_max;

public:
    AABB() = default;
    AABB(const Interval &x, const Interval &y, const Interval &z)
    {
        m_min = Point3D(x.min, y.min, z.min);
        m_max = Point3D(x.max, y.max, z.max);
    }
    AABB(const Point3D &min, const Point3D &max):
        m_min(min),
        m_max(max)
    {
    }
    ~AABB() = default;

    bool hits(const Ray &ray, HitRecord &hitrec) const
    {
        float tx1 = (m_min._x - ray.origin()._x) / ray.direction()._x;
        float tx2 = (m_max._x - ray.origin()._x) / ray.direction()._x;
        float tmin = std::min(tx1, tx2);
        float tmax = std::max(tx1, tx2);

        float ty1 = (m_min._y - ray.origin()._y) / ray.direction()._y;
        float ty2 = (m_max._y - ray.origin()._y) / ray.direction()._y;
        tmin = std::max(tmin, std::min(ty1, ty2));
        tmax = std::min(tmax, std::max(ty1, ty2));

        float tz1 = (m_min._z - ray.origin()._z) / ray.direction()._z;
        float tz2 = (m_max._z - ray.origin()._z) / ray.direction()._z;
        tmin = std::max(tmin, std::min(tz1, tz2));
        tmax = std::min(tmax, std::max(tz1, tz2));

        return tmax >= tmin && tmin < hitrec.t && tmax > 0;
    }

    Point3D centroid() const { return (m_min + m_max) / 2; }

    inline void grow(Point3D p)
    {
        m_min = Point3D(std::min(m_min._x, p._x), std::min(m_min._y, p._y), std::min(m_min._z, p._z));
        m_max = Point3D(std::max(m_max._x, p._x), std::max(m_max._y, p._y), std::max(m_max._z, p._z));
    }

    inline float area()
    {
        Point3D e = m_max - m_min; // box extent
        return e._x * e._y + e._y * e._z + e._z * e._x;
    }
};
