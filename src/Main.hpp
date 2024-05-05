/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

#pragma once
#include "Camera.hpp"
#include "Parameters.hpp"
#include "Primitives/Sphere.hpp"
#include "Scene/World.hpp"
#include "Scene/Image.hpp"

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
    Camera _camera;
    World _world;
    Image _image;

    auto run() -> int;
    auto render_real_time() -> void;
    auto arg_parse() -> bool;

protected:
private:
};
