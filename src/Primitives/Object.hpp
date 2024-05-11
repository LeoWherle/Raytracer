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
#include "Scene/BVH.hpp"
#include "Scene/World.hpp"
#include "TriangleObj.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * @brief A class containing a object loaded from a .obj file
 * Can only contain primitives of type TriangleObj
 *
 */
class Object : public BVH, public IPrimitive {
public:
    Object(const Point3D &origin, float scale, IMaterial *mat):
        _origin(origin),
        _scale(scale),
        _material(mat)
    {
    }
    ~Object() { delete _material; }

    void addTriangle(std::array<Point3D, 3> vertices, std::array<Vector3D, 3> normals)
    {
        triangles.push_back(std::make_unique<TriangleObj>(vertices, normals, _material));
    }
    void addTriangle(std::unique_ptr<TriangleObj> triangle) { triangles.push_back(std::move(triangle)); }

    bool hits(const Ray &ray, Interval ray_d, HitRecord &hitrec) const override
    {
        return BVH::hits(ray, ray_d, hitrec);
    }

    auto get_triangles() const -> const std::vector<std::unique_ptr<IPrimitive>> & { return triangles; }

    AABB boundingBox() const override { return BVH::boundingBox(); }

    Point3D centroid() const override { return BVH::centroid(); }

protected:
    Point3D _origin;
    float _scale;
    IMaterial *_material;
    std::vector<std::unique_ptr<IPrimitive>> triangles;

private:
};