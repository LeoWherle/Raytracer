/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Object
*/

#pragma once

#include "Materials/IMaterial.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Scene/World.hpp"
#include "TriangleObj.hpp"
#include <array>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief A class containing a object loaded from a .obj file
 * Can only contain primitives of type TriangleObj
 *
 */
class Object : public World {
public:
    Object(const Point3D &origin, float scale, IMaterial *mat):
        _origin(origin), _scale(scale), _material(mat)
    {
    }
    ~Object() { delete _material; }

    void addTriangle(std::array<Point3D, 3> vertices, std::array<Vector3D, 3> normals)
    {
        primitives.push_back(std::make_unique<TriangleObj>(vertices, normals, _material));
    }

protected:
    Point3D _origin;
    float _scale;
    IMaterial *_material;

private:
};