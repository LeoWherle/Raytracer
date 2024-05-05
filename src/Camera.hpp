/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Camera
*/

#pragma once

#include "Color.hpp"
#include "HitRecord.hpp"
#include "Interval.hpp"
#include "Math/MathsUtils.hpp"
#include "Math/Point3D.hpp"
#include "Math/Rectangle3D.hpp"
#include "Ray.hpp"
#include "Scene/IImage.hpp"
#include "Scene/World.hpp"
#include "math.h"
#include <execution>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

class Camera {
public:
    float aspect_ratio = 1.0f; // Can be 16:9, 4:3, etc.
    uint32_t image_width = 100;
    uint32_t samples_per_pixel = 10;
    uint32_t max_depth = 10;
    Color background;

    float vfov = 90;
    Point3D origin = Point3D(0, 0, 0);
    Point3D lookat = Point3D(0, 0, -1);
    Vector3D vup = Vector3D(0, 1, 0);

    float defocus_angle = 0; // Variation angle of rays through each pixel
    float focus_dist = 10; // Distance from camera lookfrom point to plane of perfect focus

    uint32_t image_height;

private:
    float pixel_samples_scale;
    Point3D center;
    Vector3D pixel_delta_u;
    Vector3D pixel_delta_v;
    Point3D pixel00_loc;
    Vector3D defocus_disk_u;
    Vector3D defocus_disk_v;

public:
    Camera() = default;

    void update()
    {
        image_height = uint32_t((float) image_width / (float) aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0f / (float) samples_per_pixel;

        center = origin;

        // Determine viewport dimensions.
        auto theta = mathsUtils::degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (float(image_width) / (float) image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        auto w = Vector3D::unit(origin - lookat);
        auto u = Vector3D::unit(vup.cross(w));
        auto v = w.cross(u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        Vector3D viewport_u = u * viewport_width; // Vector across viewport horizontal edge
        Vector3D viewport_v = -v * viewport_height; // Vector down viewport vertical edge

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / (float) image_width;
        pixel_delta_v = viewport_v / (float) image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - (w * static_cast<float>(focus_dist)) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5f;

        // Calculate the camera defocus disk basis vectors.
        // from
        // https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
        auto defocus_radius = focus_dist * tan(mathsUtils::degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    void move(const Vector3D &direction) { origin = origin + direction; }

    Ray new_ray(float u, float v) const
    {

        auto offset = Vector3D(mathsUtils::random_float() - 0.5f, mathsUtils::random_float() - 0.5f, 0);
        auto pixel_sample =
            pixel00_loc + (pixel_delta_u * (u + offset._x)) + (pixel_delta_v * (v + offset._y));
        auto ray_direction = pixel_sample - center;

        return Ray(center, ray_direction);
    }

    Color ray_color(const Ray &r, int depth, const World &world) const
    {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return Color(0, 0, 0);

        HitRecord rec;

        // If the ray hits nothing, return the background color.
        if (!world.hits(r, Interval(0.001f, std::numeric_limits<float>::infinity()), rec))
            return background;

        Ray scattered;
        Color attenuation;
        Color color_from_emission = rec.material->emitted(rec.u, rec.v, rec.p);

        // If the ray is scattered, modify the color by the attenuation and recurse.
        if (!rec.material->scatter(r, rec, attenuation, scattered))
            return color_from_emission;

        // Recurse with the new scattered ray, and multiply the result by the attenuation.
        Color color_from_scatter = ray_color(scattered, depth - 1, world) * attenuation;

        return color_from_emission + color_from_scatter;
    }

    void render(World &world, IImage &image)
    {
        update();
        image.resize(image_width, image_height);
        std::clog << "\rRendering: 0.00%" << std::flush;

        auto pixel_func = [&](uint32_t i, uint32_t j) {
            Color pixel_color(0, 0, 0);
            for (uint32_t sample = 0; sample < samples_per_pixel; sample++) {
                Ray r = new_ray((float) i, (float) j);
                pixel_color += ray_color(r, max_depth, world);
            }
            image.set_pixel(i, j, pixel_color * pixel_samples_scale);
        };

        // clang-format off
        std::for_each(std::execution::par_unseq, image.row_begin(), image.row_end(), [&](uint32_t j) {
        // for (uint32_t j = 0; j < image.get_height(); j++) {
            for (uint32_t i = 0; i < image.get_width(); i++) {
                pixel_func(i, j);
            };
            std::clog << "\rRendering: " << std::fixed << std::setprecision(2) << (100.0f * (float) j / (float) (image.get_height() - 1)) << "%" << std::flush;
        // };
        });
        // clang-format on
        std::clog << std::endl;
    }
};
