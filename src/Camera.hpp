/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Camera
*/

#pragma once

#include "Color.hpp"
#include "HitRecord.hpp"
#include "Math/Interval.hpp"
#include "Math/MathsUtils.hpp"
#include "Math/Matrix3D.hpp"
#include "Math/Point3D.hpp"
#include "Math/Random.hpp"
#include "Math/Rectangle3D.hpp"
#include "Ray.hpp"
#include "Scene/IImage.hpp"
#include "Scene/World.hpp"
#include "math.h"

#include <array>
#include <atomic>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <thread>
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

    void update();

    void move(const Vector3D &direction);

    void rotate(const Vector3D &axis, float angle);

    Ray new_ray(float u, float v) const;

    Color ray_color(const Ray &r, int depth, const World &world) const;

    template<bool ShowProgress = true>
    void render(World &world, IImage &image)
    {
        update();
        image.resize(image_width, image_height);
        if constexpr (ShowProgress) {
            std::clog << "\rRendering: 0.00%" << std::flush;
        }
        auto pixel_func = [&](uint32_t i, uint32_t j) {
            Color pixel_color(0, 0, 0);
            for (uint32_t sample = 0; sample < samples_per_pixel; sample++) {
                Ray r = new_ray((float) i, (float) j);
                pixel_color += ray_color(r, max_depth, world);
            }
            image.set_pixel(
                i, j, pixel_color * pixel_samples_scale, samples_per_pixel, static_cast<float>(max_depth)
            );
        };
        auto number_threads = std::thread::hardware_concurrency();
        std::atomic<uint32_t> row = 0;
        std::vector<std::atomic<uint32_t>> progress(number_threads);
        auto thread_func = [&](uint32_t thread_id) {
            for (uint32_t j = row++; j < image.get_height(); j = row++) {
                for (uint32_t i = 0; i < image.get_width(); i++) {
                    pixel_func(i, j);
                }
                if constexpr (ShowProgress) {
                    progress[thread_id].fetch_add(1);
                }
            }
        };
        std::vector<std::thread> threads;
        for (uint32_t n = 0; n < number_threads; n++) {
            threads.push_back(std::thread(thread_func, n));
        }
        if constexpr (ShowProgress) {
            while (true) {
                uint32_t total_progress = 0;
                for (auto &p : progress) {
                    total_progress += p.load();
                }
                if (total_progress == image.get_height()) {
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                auto progress_percent = (100.0f * (float) total_progress / (float) (image.get_height() - 1));
                std::clog << "\rRendering: " << std::fixed << std::setprecision(2) << progress_percent << "%"
                          << std::flush;
            }
            std::clog << std::endl;
        }
        for (auto &thread : threads) {
            thread.join();
        }
    };
};
