/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** ConeFactory
*/

#include <string>
#include <memory>
#include "ConeFactory.hpp"

std::unique_ptr<Cone> ConeFactory::createCone(const boost::property_tree::ptree &cone) const
{
    auto tip = createPoint3D(cone.get_child("tip"));
    auto direction = createVector3D(cone.get_child("direction"));
    auto height = cone.get<float>("height");
    auto radius = cone.get<float>("angle");

    const IMaterial *mat = createMaterial(cone.get_child("material"));
    auto obj = std::make_unique<Cone>(tip, height, direction, mat, radius);

    auto transformations_opt = cone.get_child_optional("transformations");
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
