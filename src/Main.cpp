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
#include "Main.hpp"
#include "Math/Rectangle3D.hpp"
#include "Parameters.hpp"
#include "Sphere.hpp"
#include "LightPoint.hpp"

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

static Color add_light_to_sphere(const Ray &ray, const Sphere &sphere, ILight &light)
{
    Color result = Color(0, 0, 0);
    double t = sphere.hits(ray);
    if (t == -1)
        return result;
    Point3D hit_point = ray.at(t);
    Vector3D normal = (hit_point - sphere._center).normalize();
    Vector3D light_direction = (hit_point - light._origin).normalize();
    double light_intensity = normal.dot(light_direction);
    if (light_intensity > 0) {
        result = sphere._color * light_intensity * light._intensity;
    }
    return result;
}

auto render_frame(sf::Uint8 *pixels, uint32_t image_width, uint32_t image_height, Camera &cam, Sphere &sphere, ILight &light)
    -> void
{
    for (uint32_t j = 0; j < image_height; ++j) {
        for (uint32_t i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);
            Color color(0.0, 0.0, 0.0);

            color = add_light_to_sphere(cam.ray(u, v), sphere, light);
            pixels[(j * image_width + i) * 4 + 0] = static_cast<sf::Uint8>(color._r);
            pixels[(j * image_width + i) * 4 + 1] = static_cast<sf::Uint8>(color._g);
            pixels[(j * image_width + i) * 4 + 2] = static_cast<sf::Uint8>(color._b);
            pixels[(j * image_width + i) * 4 + 3] = 255;
        }
    }
}

auto handle_events(sf::RenderWindow &window, Camera &cam, ILight &light) -> void
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
            case sf::Keyboard::Key::L:
                light.move(Vector3D(movespeed, 0, 0));
                break;
            case sf::Keyboard::Key::J:
                light.move(Vector3D(-movespeed, 0, 0));
                break;
            case sf::Keyboard::Key::K:
                light.move(Vector3D(0, 0, -movespeed));
                break;
            case sf::Keyboard::Key::I:
                light.move(Vector3D(0, 0, movespeed));
                break;
            case sf::Keyboard::Key::U:
                light.move(Vector3D(0, -movespeed, 0));
                break;
            case sf::Keyboard::Key::P:
                light.move(Vector3D(0, movespeed, 0));
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

auto render_real_time(uint32_t image_width, uint32_t image_height, Camera &cam, Sphere &sphere, ILight &light) -> void
{

    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Raytracer");
    sf::Uint8 *pixels = new sf::Uint8[image_width * image_height * 4];
    // framebuffer sprite
    sf::Texture texture;
    texture.create(image_width, image_height);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        handle_events(window, cam, light);
        render_frame(pixels, image_width, image_height, cam, sphere, light);
        window.clear();
        texture.update(pixels);
        window.draw(sprite);
        window.display();
    }
    delete[] pixels;
}


void write_color(std::ofstream &out, const Color &color)
{
    out << static_cast<int>(color._r) << ' ' << static_cast<int>(color._g) << ' '
        << static_cast<int>(color._b) << '\n';
}

auto Main::render_image(uint32_t image_width, uint32_t image_height, Camera &cam, Sphere &sphere, ILight &light) -> void
{
    std::string file_name = _params._output_file;
    if (file_name.empty()) {
        file_name = "output.ppm";
    }
    std::ofstream out(file_name);
    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (uint32_t j = 0; j < image_height; ++j) {
        for (uint32_t i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);
            Color color(0.0, 0.0, 0.0);

            color = add_light_to_sphere(cam.ray(u, v), sphere, light);
            write_color(out, color);
        }
    }
    std::cout << "Image saved to " << file_name << std::endl;
    out.close();
}

auto Main::run() -> int
{
    const uint32_t image_width = 400;
    const uint32_t image_height = 400;
    Sphere sphere(Point3D(0, -0.5, -1), 0.2, Color(255, 0, 0));
    LightPoint light = LightPoint(Point3D(1, -0.8, -1.5), 1);
    Camera cam;

    if (_params._gui) {
        render_real_time(image_width, image_height, cam, sphere, light);
    }
    if (!_params._scene_file.empty()) {
        render_image(image_width, image_height, cam, sphere, light);
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
