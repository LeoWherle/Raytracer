/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** TriangleFactory
*/

#include <string>
#include <memory>
#include "TriangleFactory.hpp"

std::shared_ptr<Triangle> TriangleFactory::createTriangle(const boost::property_tree::ptree &triangle) const
{
    std::vector<Point3D> vertices;

    for (boost::property_tree::ptree::value_type vertice : triangle.get_child("vertices")) {
        vertices.push_back(_point3d_factory.createPoint3D(vertice.second));
    }
    if (vertices.size() != 3) {
        throw std::runtime_error("Triangle must have 3 vertices");
    }

    IMaterial *mat = _material_factory.createMaterial(triangle.get_child("material"));

    return std::make_shared<Triangle>(vertices[0], vertices[1], vertices[2], mat);
}
