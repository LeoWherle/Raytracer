/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** CylinderFactory
*/

#include "CylinderFactory.hpp"
#include <string>
#include <memory>
#include <list>

static std::list<std::string> valid_transformations = {
    "translation",
    "rotation"
};

using wrong_child = boost::property_tree::ptree_bad_path;

std::unique_ptr<Cylinder> CylinderFactory::createCylinder(const boost::property_tree::ptree &cylinder) const
{
    auto origin = createPoint3D(cylinder.get_child("position"));
    auto radius = cylinder.get<float>("radius");
    auto direction = createVector3D(cylinder.get_child("direction"));
    auto material = cylinder.get<std::string>("material.material");

    IMaterial *mat = createMaterial(cylinder.get_child("material"));
    auto obj = std::make_unique<Cylinder>(origin, direction, radius, mat);

    try {
        auto transformations = cylinder.get_child("transformations");

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
