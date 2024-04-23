/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

#include <fstream>
#include <iostream>

#include "Main.hpp"
#include "Math.hpp"

auto Main::arg_parse(int ac, char **av) -> bool
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " [scene file]" << std::endl;
        return false;
    }
    return true;
}

void write_color(std::ofstream &out, const Vector3D &color)
{
    out << static_cast<int>(color._x) << ' ' << static_cast<int>(color._y) << ' '
        << static_cast<int>(color._z) << '\n';
}

auto Main::run(int ac, char **av) -> int
{
    if (!arg_parse(ac, av))
        return 84;

    const int image_width = 400;
    const int image_height = 400;

    std::ofstream out("output.ppm");
    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    Camera cam;
    Sphere sphere(Point3D(0, -0.5, -1), 0.2);

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);
            Ray ray = cam.ray(u, v);
            Vector3D color(0.0, 0.0, 0.0);

            if (sphere.hits(ray)) {
                color = Vector3D(200, 0, 0);
            } else {
                color = Vector3D(29, 32, 39);
            }
            write_color(out, color);
        }
    }
    out.close();
    return 0;
}

auto main(int ac, char **av) -> int
{
    Main main;
    int exitCode = 0;

    try {
        exitCode = main.run(ac, av);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exitCode = 84;
    }
    return exitCode;
}
