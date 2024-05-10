/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** TriangleFactory
*/

#include <string>
#include <memory>
#include <list>
#include "TriangleFactory.hpp"

static std::list<std::string> valid_transformations = {
    "translation",
    "rotation"
};

using wrong_child = boost::property_tree::ptree_bad_path;

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

    try {
        auto transformations = triangle.get_child("transformations");

        for (auto &choices : valid_transformations) {
            try {
                auto trans = transformations.get_child(choices);

                if (choices == "translation") {obj->translate(createPoint3D(trans));}
                else if (choices == "rotation") {obj->rotate(createPoint3D(trans)); }
                else {}
            } catch(const wrong_child &e) {
                continue;
            }
        }
    } catch(const wrong_child &e) {}

    return obj;
}
