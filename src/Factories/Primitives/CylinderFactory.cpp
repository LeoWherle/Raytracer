/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** CylinderFactory
*/

#include "CylinderFactory.hpp"
#include <string>
#include <memory>

std::unique_ptr<Cylinder> CylinderFactory::createCylinder(const boost::property_tree::ptree &cylinder) const
{
    auto origin = createPoint3D(cylinder.get_child("position"));
    auto radius = cylinder.get<float>("radius");
    auto direction = createVector3D(cylinder.get_child("direction"));
    auto material = cylinder.get<std::string>("material.material");
    auto height = cylinder.get<float>("height");

    const IMaterial *mat = createMaterial(cylinder.get_child("material"));
    auto obj = std::make_unique<Cylinder>(origin, direction, radius, mat, height);

    auto transformations_opt = cylinder.get_child_optional("transformations");
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
