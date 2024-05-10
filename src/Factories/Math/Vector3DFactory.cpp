/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Vector3DFactory
*/

#include "Vector3DFactory.hpp"

Vector3D Vector3DFactory::createVector3D(const boost::property_tree::ptree &position) const
{
    return Vector3D(
        position.get<float>("x"), position.get<float>("y"), position.get<float>("z")
    );
}