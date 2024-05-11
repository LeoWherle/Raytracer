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

    const IMaterial *mat = createMaterial(triangle.get_child("material"));
    auto obj = std::make_unique<Triangle>(vertices[0], vertices[1], vertices[2], mat);

    auto transformations_opt = triangle.get_child_optional("transformations");
    if (transformations_opt) {
        auto transformations = *transformations_opt;

        for (auto &choices : valid_transformations) {
            auto trans_opt = transformations.get_child_optional(choices);

            if (trans_opt) {
                auto trans = *trans_opt;

                if (choices == "translation") {
                    obj->translate(createPoint3D(trans));
                } else if (choices == "rotation") {
                    obj->rotate(createPoint3D(trans));
                }
            }
        }
    }

    return obj;
}
