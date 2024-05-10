/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** World
*/

#pragma once

#include <memory>
#include <vector>

#include "HitRecord.hpp"
#include "Math/Interval.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Ray.hpp"

class World : public IPrimitive {
public:
    World() = default;
    ~World() = default;

    std::vector<std::unique_ptr<IPrimitive>> primitives;

    void addPrimitive(std::unique_ptr<IPrimitive> primitive);

    virtual bool hits(const Ray &r, Interval ray_d, HitRecord &rec) const override;

    AABB boundingBox() const override
    {
        Point3D min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
        Point3D max(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
        for (const auto &primitive : primitives) {
            AABB aabb = primitive->boundingBox();
            min._x = std::fmin(min._x, aabb.m_min._x);
            min._y = std::fmin(min._y, aabb.m_min._y);
            min._z = std::fmin(min._z, aabb.m_min._z);
            max._x = std::fmax(max._x, aabb.m_max._x);
            max._y = std::fmax(max._y, aabb.m_max._y);
            max._z = std::fmax(max._z, aabb.m_max._z);
        }
        return AABB(min, max);
    }

    Point3D centroid() const override
    {
        Point3D centroid;
        for (const auto &primitive : primitives) {
            centroid += primitive->centroid();
        }
        centroid /= static_cast<float>(primitives.size());
        return centroid;
    }

protected:
private:
};
