/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** CameraFactory
*/

#include "CameraFactory.hpp"

Camera CameraFactory::createCamera(const boost::property_tree::ptree &pt) const
{
    Camera camera;

    camera.aspect_ratio = 16.0f / 9.0f;
    camera.image_width = pt.get<int>("resolution.width");
    camera.samples_per_pixel = pt.get<int>("RayPerPixel");
    camera.max_depth = pt.get<int>("MaxBounces");
    camera.background._r = pt.get<float>("BackgroundColor.r");
    camera.background._g = pt.get<float>("BackgroundColor.g");
    camera.background._b = pt.get<float>("BackgroundColor.b");

    camera.vfov = pt.get<float>("fieldOfView");
    camera.origin._x = pt.get<float>("position.x");
    camera.origin._y = pt.get<float>("position.y");
    camera.origin._z = pt.get<float>("position.z");
    camera.lookat._x = pt.get<float>("rotation.x");
    camera.lookat._y = pt.get<float>("rotation.y");
    camera.lookat._z = pt.get<float>("rotation.z");
    camera.vup = Vector3D(0, 1, 0);

    camera.defocus_angle = pt.get<float>("DefocusAngle");
    return camera;
}
