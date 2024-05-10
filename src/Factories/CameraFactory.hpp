/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** CameraFactory
*/

#pragma once

#include "Camera.hpp"
#include <boost/property_tree/ptree.hpp>

class CameraFactory {
public:
    CameraFactory() = default;
    ~CameraFactory() = default;

    Camera createCamera(const boost::property_tree::ptree &pt) const;
};
