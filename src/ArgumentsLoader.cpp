/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** ParametersLoader
*/

#include "ArgumentsLoader.hpp"

void ArgumentsLoader::parse(int ac, char **av) noexcept
{
    for (int i = 1; i < ac; i++) {
        std::string arg = av[i];
        if (arg[0] == '-') {
            std::string key = arg.substr(1);
            if (i + 1 < ac && av[i + 1][0] != '-') {
                _flag_params[key] = av[i + 1];
                i++;
            } else {
                _flag_params[key] = "";
            }
        } else {
            _positional_params.push_back(arg);
        }
    }
}

std::string ArgumentsLoader::get(const std::string &key)
{
    if (has(key) == false) {
        throw MissingArgument("Argument not found");
    }
    return _flag_params[key];
}

std::string ArgumentsLoader::get(uint32_t index)
{
    if (index >= _positional_params.size()) {
        throw MissingArgument("Positional argument not found");
    }
    return _positional_params[index];
}

bool ArgumentsLoader::has(const std::string &key) { return _flag_params.find(key) != _flag_params.end(); }
void ArgumentsLoader::set(const std::string &key, const std::string &value) { _flag_params[key] = value; }
void ArgumentsLoader::clear(void)
{
    _flag_params.clear();
    _positional_params.clear();
}
void ArgumentsLoader::visit(std::function<void(const std::string &, const std::string &)> visitor)
{
    for (auto &param : _positional_params) {
        visitor("", param);
    }
    for (auto &param : _flag_params) {
        visitor(param.first, param.second);
    }
}

std::ostream &operator<<(std::ostream &os, const ArgumentsLoader &params)
{
    os << "Positional parameters:" << std::endl;
    for (uint32_t i = 0; i < params._positional_params.size(); i++) {
        os << i << " => " << params._positional_params[i] << std::endl;
    }
    os << "Flag parameters:" << std::endl;
    for (auto &param : params._flag_params) {
        os << param.first << " => " << param.second << std::endl;
    }
    return os;
}