/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** ObjFactory
*/

#include "ObjFactory.hpp"
#include "ObjLoader.hpp"

std::unique_ptr<Object> ObjFactory::createObj(const boost::property_tree::ptree &pt) const
{
    auto filename = pt.get<std::string>("filename");
    auto origin = createPoint3D(pt.get_child("position"));
    auto scale = pt.get<float>("scale");
    auto mat = createMaterial(pt.get_child("material"));

    return ObjLoader::load(filename, origin, scale, mat);
}