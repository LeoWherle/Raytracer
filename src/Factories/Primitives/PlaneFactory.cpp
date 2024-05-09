/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PlaneFactory
*/

#include <string>
#include <memory>
#include <list>
#include "PlaneFactory.hpp"

static std::list<std::string> valid_transformations = {
    "translation",
    "rotation"
};

using wrong_child = boost::property_tree::ptree_bad_path;

std::unique_ptr<Plane> PlaneFactory::createPlane(const boost::property_tree::ptree &plane) const
{
    auto origin = createPoint3D(plane.get_child("position"));
    auto normal = createVector3D(plane.get_child("normal"));
    auto material = plane.get<std::string>("material.material");
    
    IMaterial *mat = createMaterial(plane.get_child("material"));
    auto obj = std::make_unique<Plane>(origin, normal, mat);
    
    try {
        auto transformations = plane.get_child("transformations");

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
