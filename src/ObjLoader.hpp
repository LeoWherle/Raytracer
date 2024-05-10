/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** ObjLoader
*/

#pragma once

#include "Materials/IMaterial.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Primitives/Object.hpp"
#include "Scene/World.hpp"
#include <array>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief A class to load .obj files
 *
 */
class ObjLoader {
private:
    static auto parse_vertex(const std::string &line) -> Point3D;
    static auto parse_normal(const std::string &line) -> Vector3D;
    static auto parse_index(const std::string &line) -> std::array<int, 3>;

public:
    static auto load(const std::string &filename, const Point3D &origin, float scale, const IMaterial *mat)
        -> std::unique_ptr<Object>;

protected:
private:
};
