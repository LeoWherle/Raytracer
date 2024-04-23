/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

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

auto Main::run(int ac, char **av) -> int
{
    if (!arg_parse(ac, av))
        return 84;

    Camera cam;
    Sphere s(Point3D(1, 1, -1), 0.5);

    std::cout << "P3" << std::endl << 1 / 0.01 << " " << 1 / 0.01 << std::endl;
    std::cout << 255 << std::endl;
    for (double i = 0; i < 2; i += 0.01) {
        for (double j = 0; j < 2; j += 0.01) {
            double u = i;
            double v = j;
            Ray r = cam.ray(u, v);
            if (s.hits(r)) {
                // red
                std::cout << 255 << 0 << 0 << std::endl;
            } else {
                std::cout << 0 << 0 << 0 << std::endl;
            }
        }
    }
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
