/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** TriangleFactory
*/

#include <string>
#include <memory>
#include "TriangleFactory.hpp"

std::unique_ptr<Triangle> TriangleFactory::createTriangle(const boost::property_tree::ptree &triangle) const
{
    std::vector<Point3D> vertices;

    for (boost::property_tree::ptree::value_type vertice : triangle.get_child("vertices")) {
        vertices.push_back(createPoint3D(vertice.second));
    }
    if (vertices.size() != 3) {
        throw std::runtime_error("Triangle must have 3 vertices");
    }

    IMaterial *mat = createMaterial(triangle.get_child("material"));

    return std::make_unique<Triangle>(vertices[0], vertices[1], vertices[2], mat);
}
