/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ColorFactory
*/

#include "ColorFactory.hpp"

Color ColorFactory::createColor(const boost::property_tree::ptree &pt) const
{
    return Color(
        pt.get<float>("r"), pt.get<float>("g"), pt.get<float>("b")
    );
}