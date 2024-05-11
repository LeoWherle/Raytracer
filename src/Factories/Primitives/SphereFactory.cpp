/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** SphereFactory
*/

#include <string>
#include <memory>
#include "SphereFactory.hpp"

std::unique_ptr<Sphere> SphereFactory::createSphere(const boost::property_tree::ptree &sphere) const
{
    auto center = createPoint3D(sphere.get_child("position"));
    auto radius = sphere.get<float>("radius");
    auto material = sphere.get<std::string>("material.material");

    const IMaterial *mat = createMaterial(sphere.get_child("material"));
    auto obj = std::make_unique<Sphere>(center, radius, mat);
    

    auto transformations_opt = sphere.get_child_optional("transformations");
    if (transformations_opt) {
        auto transformations = *transformations_opt;

        for (auto &choices : valid_transformations) {
            auto trans_opt = transformations.get_child_optional(choices);

            if (trans_opt && choices == "translation") {
                obj->translate(createPoint3D(*trans_opt));
            }
        }
    }
    return obj;
}
