/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Parameters
*/

#pragma once

#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class ArgumentsLoader {
public:
    ArgumentsLoader() = default;
    ~ArgumentsLoader() = default;

    // clang-format off
    class MissingArgument : public std::exception {
    private:
        const std::string _message;

    public:
        explicit MissingArgument(const std::string &message): _message(message) {}
        explicit MissingArgument(const char *const message): _message(message) {}
        virtual ~MissingArgument() noexcept { }
        const char *what() const noexcept override { return _message.c_str(); }
    };
    // clang-format on
protected:
    std::map<std::string, std::string> _flag_params;
    std::vector<std::string> _positional_params;

public:
    void parse(int ac, char **av) noexcept;

    std::string get(const std::string &key);
    std::string get(uint32_t index);
    bool has(const std::string &key);
    bool has(uint32_t index) { return index < _positional_params.size(); }
    void set(const std::string &key, const std::string &value);
    void clear(void);
    void remove(const std::string &key) { _flag_params.erase(key); }

    // visits all the parameters (positional and flag parameters)
    void visit(std::function<void(const std::string &, const std::string &)> visitor);
    friend std::ostream &operator<<(std::ostream &os, const ArgumentsLoader &params);
};
