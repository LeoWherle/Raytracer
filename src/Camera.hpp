/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Camera
*/

#pragma once

#include "Color.hpp"
#include "HitRecord.hpp"
#include "Image.hpp"
#include "Interval.hpp"
#include "Math/MathsUtils.hpp"
#include "Math/Point3D.hpp"
#include "Math/Rectangle3D.hpp"
#include "Ray.hpp"
#include "Scene/World.hpp"
#include "math.h"
#include <iostream>
#include <math.h>

static inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

static void write_color(std::ostream &out, const Color &pixel_color)
{
    auto r = pixel_color._r;
    auto g = pixel_color._g;
    auto b = pixel_color._b;

    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

class Camera {
public:
    double aspect_ratio = 1.0; // Can be 16:9, 4:3, etc.
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;
    Color background;

    double vfov = 90;
    Point3D origin = Point3D(0, 0, 0);
    Point3D lookat = Point3D(0, 0, -1);
    Vector3D vup = Vector3D(0, 1, 0);

    double defocus_angle = 0; // Variation angle of rays through each pixel
    double focus_dist = 10; // Distance from camera lookfrom point to plane of perfect focus

    int image_height;

private:
    double pixel_samples_scale;
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
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = origin;

        // Determine viewport dimensions.
        auto theta = mathsUtils::degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

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
        auto defocus_radius = focus_dist * tan(mathsUtils::degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    void move(const Vector3D &direction) { origin = origin + direction; }

    Ray get_ray(double u, double v) const
    {

        auto offset = Vector3D(mathsUtils::random_double() - 0.5, mathsUtils::random_double() - 0.5, 0);
        auto pixel_sample =
            pixel00_loc + (pixel_delta_u * (u + offset._x)) + (pixel_delta_v * (v + offset._y));

        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;
        auto ray_time = mathsUtils::random_double();

        return Ray(ray_origin, ray_direction, ray_time);
    }

    Point3D defocus_disk_sample() const
    {
        // Returns a random point in the camera defocus disk.
        auto point = mathsUtils::random_in_unit_disks();
        return center + (defocus_disk_u * point._x) + (defocus_disk_v * point._y);
    }

    Color ray_color(const Ray &r, int depth, const World &world) const
    {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return Color(0, 0, 0);

        HitRecord rec;

        // If the ray hits nothing, return the background color.
        if (!world.hits(r, Interval(0.001, std::numeric_limits<double>::infinity()), rec))
            return background;

        Ray scattered;
        Color attenuation;
        Color color_from_emission = rec.material->emitted(rec.u, rec.v, rec.p);

        if (!rec.material->scatter(r, rec, attenuation, scattered))
            return color_from_emission;

        Color color_from_scatter = ray_color(scattered, depth - 1, world) * attenuation;

        return color_from_emission + color_from_scatter;
    }

    void render(World &world, Image &image)
    {
        update();
        image.resize(image_width, image_height);
        for (int j = 0; j < image_height; j++) {
            for (int i = 0; i < image_width; i++) {
                Color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    Ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                image.set_pixel(i, j, pixel_color * pixel_samples_scale);
            }
        }
    }
};
