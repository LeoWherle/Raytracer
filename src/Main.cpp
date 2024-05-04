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

static Color
add_light_to_sphere(const Ray &ray, std::shared_ptr<Sphere> sphere, std::shared_ptr<ILight> light)
{
    Color result = Color(0, 0, 0);
    double t = sphere->hits(ray);
    if (t == -1)
        return result;
    Point3D hit_point = ray.at(t);
    Vector3D normal = (hit_point - sphere->_center).normalize();
    Vector3D light_direction = (hit_point - light->_origin).normalize();
    double light_intensity = normal.dot(light_direction);
    if (light_intensity > 0) {
        result = sphere->_color * light_intensity * light->_intensity;
    }
    return result;
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
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Raytracer", sf::Style::Close);
    sf::Texture texture;
    texture.create(image_width, image_height);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        handle_events(window, _camera);
        _camera.render(_image, _world);
        window.clear();
        texture.update(pixels);
        window.draw(sprite);
        window.display();
    }
}

auto Main::run() -> int
{
    const uint32_t image_width = 400;
    const uint32_t image_height = 400;

    _world.addPrimitive(std::make_shared<Sphere>(Point3D(0, -0.5, -1), 0.2, Color(255, 0, 0)));
    _world.addLight(std::make_shared<LightPoint>(Point3D(1, -0.8, -1.5), 1));

    if (_params._gui) {
        render_real_time(pixels, image_width, image_height);
    }
    if (!_params._scene_file.empty()) {
        _camera.render_image(_world, _image);
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
