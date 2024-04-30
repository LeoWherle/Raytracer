/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "Camera.hpp"
#include "Parameters.hpp"
#include "Sphere.hpp"
#include "ILight.hpp"

class Main {
public:
    Main(int ac, char *av[]):
        _ac(ac),
        _av(av)
    {
    }
    ~Main() = default;

    int _ac;
    char **_av;
    Parameters _params;
    auto run() -> int;

    auto render_image(uint32_t image_width, uint32_t image_height, Camera &cam, Sphere &sphere, ILight &light) -> void;

    auto arg_parse() -> bool;

protected:
private:
};

#endif /* !MAIN_HPP_ */
