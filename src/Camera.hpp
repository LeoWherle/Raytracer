/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Camera
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Rectangle3D.hpp"
#include "Ray.hpp"
#include "math.h"

class Camera {
public:
    float aspect_ratio = 1.0; // Can be 16:9, 4:3, etc.
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;
    Color background;

    float vfov = 90;
    Point3D origin = Point3D(0, 0, 0);
    Point3D lookat = Point3D(0, 0, -1);
    Vector3D vup = Vector3D(0, 1, 0);

    float defocus_angle = 0; // Variation angle of rays through each pixel
    float focus_dist = 10; // Distance from camera lookfrom point to plane of perfect focus

private:
    int image_height;
    float pixel_samples_scale;
    Point3D center;
    Vector3D pixel_delta_u;
    Vector3D pixel_delta_v;
    Point3D pixel00_loc;
    Vector3D defocus_disk_u;
    Vector3D defocus_disk_v;

    Camera()
    {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = origin;

        // Determine viewport dimensions.
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (float(image_width) / image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        auto w = Vector3D::unit(origin - lookat);
        auto u = Vector3D::unit(vup.cross(w));
        auto v = w.cross(u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        Vector3D viewport_u = u * viewport_width; // Vector across viewport horizontal edge
        Vector3D viewport_v = -v * viewport_height; // Vector down viewport vertical edge

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - (w * static_cast<double>(focus_dist)) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    Ray ray(double u, double v) const
    {
        Point3D point = _screen.pointAt(u, v);
        Vector3D direction = point - _origin;
        return Ray(_origin, direction);
    }

    void move(const Vector3D &direction) { _origin = _origin + direction; }

private:
    Point3D _origin;
    Rectangle3D _screen;
};
