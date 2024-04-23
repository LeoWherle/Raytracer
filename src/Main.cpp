/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <fstream>
#include <iostream>

#include "Camera.hpp"
#include "Main.hpp"
#include "Rectangle3D.hpp"
#include "Sphere.hpp"

#include <SFML/Graphics.hpp>

auto Main::arg_parse(int ac, char **av) -> bool
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " [scene file]" << std::endl;
        return false;
    }
    return true;
}

void write_color(std::ofstream &out, const Vector3D &color)
{
    out << static_cast<int>(color._x) << ' ' << static_cast<int>(color._y) << ' '
        << static_cast<int>(color._z) << '\n';
}

auto render(sf::Uint8 *pixels, int image_width, int image_height, Camera &cam) -> void
{
    Sphere sphere(Point3D(0, -0.5, -1), 0.2);

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);
            Ray ray = cam.ray(u, v);
            Vector3D color(0.0, 0.0, 0.0);

            if (sphere.hits(ray)) {
                color = Vector3D(200, 0, 0);
            } else {
                color = Vector3D(29, 32, 39);
            }
            // write_color(out, color);
            pixels[(j * image_width + i) * 4 + 0] = static_cast<sf::Uint8>(color._x);
            pixels[(j * image_width + i) * 4 + 1] = static_cast<sf::Uint8>(color._y);
            pixels[(j * image_width + i) * 4 + 2] = static_cast<sf::Uint8>(color._z);
            pixels[(j * image_width + i) * 4 + 3] = 255;
        }
    }
}

auto Main::run(int ac, char *av[]) -> int
{
    if (!arg_parse(ac, av))
        return 84;

    const int image_width = 400;
    const int image_height = 400;
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Raytracer");

    // framebuffer for the window
    sf::Uint8 *pixels = new sf::Uint8[image_width * image_height * 4];
    // framebuffer sprite
    sf::Texture texture;
    texture.create(image_width, image_height);
    sf::Sprite sprite(texture);

    // std::ofstream out("output.ppm");
    // out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    sf::Event event;

    Camera cam;

    constexpr auto movespeed = 0.01;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
            switch (event.type) {

            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Key::Down:
                case sf::Keyboard::Key::S:
                    cam.move(Vector3D(0, 0, movespeed));
                    break;
                case sf::Keyboard::Key::Up:
                case sf::Keyboard::Key::Z:
                    cam.move(Vector3D(0, 0, -movespeed));
                    break;
                case sf::Keyboard::Key::Right:
                case sf::Keyboard::Key::D:
                    cam.move(Vector3D(-movespeed, 0, 0));
                    break;
                case sf::Keyboard::Key::Left:
                case sf::Keyboard::Key::Q:
                    cam.move(Vector3D(movespeed, 0, 0));
                    break;
                case sf::Keyboard::Key::Space:
                    cam.move(Vector3D(0, movespeed, 0));
                    break;
                case sf::Keyboard::Key::LShift:
                    cam.move(Vector3D(0, -movespeed, 0));
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
#pragma GCC diagnostic pop
        render(pixels, image_width, image_height, cam);
        window.clear();
        texture.update(pixels);
        window.draw(sprite);
        window.display();
    }
    delete[] pixels;

    // out.close();
    return 0;
}

auto main(int ac, char *av[]) -> int
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
