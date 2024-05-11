/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PlaneFactory
*/

#include <string>
#include <memory>
#include "PlaneFactory.hpp"

std::unique_ptr<Plane> PlaneFactory::createPlane(const boost::property_tree::ptree &plane) const
{
    auto origin = createPoint3D(plane.get_child("position"));
    auto normal = createVector3D(plane.get_child("normal"));
    auto material = plane.get<std::string>("material.material");
    
    const IMaterial *mat = createMaterial(plane.get_child("material"));
    auto obj = std::make_unique<Plane>(origin, normal, mat);
    
    auto transformations_opt = plane.get_child_optional("transformations");
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
