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
        _help = _loader.has("help") || _loader.has("h");
        if (_loader.has("out")) {
            _output_file = _loader.get("out");
        }
        if (_loader.has("o")) {
            _output_file = _loader.get("o");
        }
        if (_gui && _output_file.empty()) {
            _output_file = "output.png";
        }
        if (_output_file.empty()) {
            _output_file = "output.ppm";
        }
        if (_loader.has(0)) {
            _scene_file = _loader.get(0);
        } else {
            throw ArgumentsLoader::MissingArgument("Scene file not found");
        }
    }

protected:
private:
};
