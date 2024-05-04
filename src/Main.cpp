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
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>

#include "Camera.hpp"
#include "Lights/LightPoint.hpp"
#include "Main.hpp"
#include "Math/Rectangle3D.hpp"
#include "Parameters.hpp"
#include "Primitives/Sphere.hpp"

#include <SFML/Graphics.hpp>
#include <ostream>
#include "Materials/BaseMaterial.hpp"
#include <string>

auto Main::arg_parse() -> bool
{
    try {
        _params.load(_ac, _av);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: " << _av[0] << " [scene file]" << std::endl;
        return false;
    }
    return true;
}

auto handle_events(sf::RenderWindow &window, Camera &cam) -> void
{
    sf::Event event;
    constexpr auto movespeed = 0.01;
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
#pragma GCC diagnostic pop
    }
}

auto Main::render_real_time() -> void
{
    sf::RenderWindow window(
        sf::VideoMode(_camera.image_width, _camera.image_height), "Raytracer", sf::Style::Close
    );
    sf::Texture texture;
    texture.create(_camera.image_width, _camera.image_height);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        handle_events(window, _camera);
        _camera.render(_world, _image);
        window.clear();
        texture.update(_image.get_stream());
        window.draw(sprite);
        window.display();
    }
}

auto Main::run() -> int
{
    _world.addPrimitive(
        std::make_shared<Sphere>(Point3D(0, -0.5, -1), 0.2, std::make_shared<BaseMaterial>(Color(255, 0, 0)))
    );

    if (_params._gui) {
        render_real_time();
    }
    if (!_params._scene_file.empty()) {
        _camera.render(_world, _image);
        _image.writePPM(_params._scene_file);
    }
    return 0;
}

auto main(int ac, char *argv[]) -> int
{
    Main main(ac, argv);
    int exitCode = 0;

    try {
        if (!main.arg_parse()) {
            return 84;
        }
        exitCode = main.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exitCode = 84;
    }
    return exitCode;
}
