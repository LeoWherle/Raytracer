/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Point3DFactory
*/

#include "Point3DFactory.hpp"

Point3D Point3DFactory::createPoint3D(const boost::property_tree::ptree &position) const
{
    return Point3D(
        position.get<float>("x"), position.get<float>("y"), position.get<float>("z")
    );
}