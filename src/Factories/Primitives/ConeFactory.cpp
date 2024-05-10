/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** ConeFactory
*/

#include <string>
#include <memory>
#include <list>
#include "ConeFactory.hpp"

static std::list<std::string> valid_transformations = {
    "translation",
    "rotation"
};

using wrong_child = boost::property_tree::ptree_bad_path;

std::unique_ptr<Cone> ConeFactory::createCone(const boost::property_tree::ptree &cone) const
{
    auto tip = createPoint3D(cone.get_child("tip"));
    auto radius = cone.get<float>("radius");
    auto axis = createVector3D(cone.get_child("axis"));
    auto surface = createPoint3D(cone.get_child("surface"));

    IMaterial *mat = createMaterial(cone.get_child("material"));
    auto obj = std::make_unique<Cone>(tip, surface, axis, mat, radius);

    try {
        auto transformations = cone.get_child("transformations");

        for (auto &choices : valid_transformations) {
            try {
                auto trans = transformations.get_child(choices);

                if (choices == "translation") {
                    obj->translate(createPoint3D(trans));
                }
                if (choices == "rotation") {
                    obj->rotate(createPoint3D(trans));
                }
            } catch(const wrong_child &e) {continue;}
        }
    } catch(const wrong_child &e) {}

    return obj;
}
