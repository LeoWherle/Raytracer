/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Parameters
*/

#pragma once

#include "ArgumentsLoader.hpp"
#include <string>

class Parameters {
public:
    Parameters() = default;
    ~Parameters() = default;

    ArgumentsLoader _loader;
    bool _gui = false;
    bool _help = false;
    std::string _output_file;
    std::string _scene_file;

    void load(int ac, char **av)
    {
        _loader.parse(ac, av);
        _gui = _loader.has("gui");
        _help = _loader.has("help");
        if (_loader.has("output")) {
            _output_file = _loader.get("output");
        }
        if (_loader.has(0)) {
            _scene_file = _loader.get(0);
        } else {
            if (!_gui) {
                throw ArgumentsLoader::MissingArgument("Scene file not found");
            }
        }
    }

protected:
private:
};
