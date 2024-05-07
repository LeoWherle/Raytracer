/*
** EPITECH PROJECT, 2024
** RayBan
** File description:
** Parameters
*/

#include "Parameters.hpp"

void Parameters::load(int ac, char **av)
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
    if (!_gui && _output_file.empty()) {
        _output_file = "output.bmp";
    }
    if (_help) {
        throw ArgumentsLoader::HelpArgument("Help:");
    }
    if (_loader.has(0)) {
        _scene_file = _loader.get(0);
    } else {
        throw ArgumentsLoader::MissingArgument("Scene file not found");
    }
}
