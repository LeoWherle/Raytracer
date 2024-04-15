/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

class Main {
public:
    Main() = default;
    ~Main() = default;

    auto run(int ac, char **av) -> int;

protected:
    auto arg_parse(int ac, char **av) -> bool;

private:
};

#endif /* !MAIN_HPP_ */
