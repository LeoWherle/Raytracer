/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** World
*/

#pragma once

#include <memory>
#include <vector>

#include "Camera.hpp"
#include "Lights/ILight.hpp"
#include "Primitives/IPrimitive.hpp"

class World : public IPrimitive {
public:
    World() = default;
    ~World() = default;

    std::vector<std::shared_ptr<IPrimitive>> primitives;
    std::vector<std::shared_ptr<ILight>> lights;
    Camera camera;

    void addPrimitive(std::shared_ptr<IPrimitive> primitive) { primitives.push_back(move(primitive)); }
    void addLight(std::shared_ptr<ILight> light) { lights.push_back(move(light)); }

    double hits(const Ray &ray) const override
    {
        double closest = -1;
        for (const auto &primitive : primitives) {
            double t = primitive->hits(ray);
            if (t > 0 && (t < closest || closest == -1)) {
                closest = t;
            }
        }
        return closest;
    }

protected:
private:
};
