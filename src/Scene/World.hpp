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

    void addPrimitive(std::shared_ptr<IPrimitive> primitive);

    bool hits(const Ray &r, Interval ray_d, HitRecord &rec) const override;

protected:
private:
};
