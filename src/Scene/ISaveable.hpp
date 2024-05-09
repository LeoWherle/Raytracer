/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** ISaveable
*/

#pragma once

#include <string>

class ISaveable {
public:
    virtual ~ISaveable() = default;

    virtual void save(const std::string &filename) const = 0;

protected:
private:
};
