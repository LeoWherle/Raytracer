/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** SphereFactory
*/

#include <string>
#include <memory>
#include <list>
#include "SphereFactory.hpp"

static std::list<std::string> valid_transformations = {
    "translation"
};

using wrong_child = boost::property_tree::ptree_bad_path;

std::unique_ptr<Sphere> SphereFactory::createSphere(const boost::property_tree::ptree &sphere) const
{
    auto center = createPoint3D(sphere.get_child("position"));
    auto radius = sphere.get<float>("radius");
    auto material = sphere.get<std::string>("material.material");

    IMaterial *mat = createMaterial(sphere.get_child("material"));
    auto obj = std::make_unique<Sphere>(center, radius, mat);
    
    try {
        auto transformations = sphere.get_child("transformations");

        for (auto &choices : valid_transformations) {
            try {
                auto trans = transformations.get_child(choices);

                if (choices == "translation") {
                    obj->translate(createPoint3D(trans));
                }
            } catch(const wrong_child &e) {
                continue;
            }
        }
    } catch(const wrong_child &e) {}

    return obj;
}
