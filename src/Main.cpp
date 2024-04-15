/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

#include "Main.hpp"
#include <iostream>

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
