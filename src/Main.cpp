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

static Color add_light_to_sphere(const Ray &ray, Sphere &sphere, ILight &light)
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

auto render_frame(
    sf::Uint8 *pixels, uint32_t image_width, uint32_t image_height, Camera &cam,
    std::shared_ptr<IPrimitive> primitive, std::shared_ptr<ILight> light
) -> void
{
    auto sphere = Sphere(Point3D(0, -0.5, -1), 0.2, Color(255, 0, 0));
    auto light_point = LightPoint(Point3D(1, -0.8, -1.5), 1);
    for (uint32_t j = 0; j < image_height; ++j) {
        for (uint32_t i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);

            Color color = add_light_to_sphere(cam.ray(u, v), sphere, light_point);
            pixels[(j * image_width + i) * 4 + 0] = color.getR();
            pixels[(j * image_width + i) * 4 + 1] = color.getG();
            pixels[(j * image_width + i) * 4 + 2] = color.getB();
            pixels[(j * image_width + i) * 4 + 3] = 255;
        }
    }
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

auto Main::render_real_time(sf::Uint8 *pixels, uint32_t image_width, uint32_t image_height) -> void
{
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Raytracer", sf::Style::Close);
    sf::Texture texture;
    texture.create(image_width, image_height);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        handle_events(window, _world.camera);
        for (auto &primitive : _world.primitives) {
            render_frame(pixels, image_width, image_height, _world.camera, primitive, _world.lights[0]);
        }
        window.clear();
        texture.update(pixels);
        window.draw(sprite);
        window.display();
    }
}

static void
writePixelInPPM(std::ofstream &out, sf::Uint8 *pixels, uint32_t i, uint32_t j, uint32_t image_width)
{
    out << static_cast<int>(pixels[(j * image_width + i) * 4 + 0]) << ' '
        << static_cast<int>(pixels[(j * image_width + i) * 4 + 1]) << ' '
        << static_cast<int>(pixels[(j * image_width + i) * 4 + 2]) << '\n';
}

auto Main::render_image(sf::Uint8 *pixels, uint32_t image_width, uint32_t image_height) -> void
{
    std::string file_name = _params._output_file.empty() ? "output.ppm" : _params._output_file;
    std::ofstream out(file_name);
    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (uint32_t j = 0; j < image_height; ++j) {
        for (uint32_t i = 0; i < image_width; ++i) {
            writePixelInPPM(out, pixels, i, j, image_width);
        }
    }
    std::cout << "Image saved to " << file_name << std::endl;
    out.close();
}

auto Main::run() -> int
{
    const uint32_t image_width = 400;
    const uint32_t image_height = 400;
    LightPoint light = LightPoint(Point3D(1, -0.8, -1.5), 1);
    Camera cam;

    _world.addPrimitive(std::make_shared<Sphere>(Point3D(0, -0.5, -1), 0.2, Color(255, 0, 0)));
    _world.addLight(std::make_shared<LightPoint>(Point3D(1, -0.8, -1.5), 1));
    sf::Uint8 *pixels = new sf::Uint8[image_width * image_height * 4];

    if (_params._gui) {
        render_real_time(pixels, image_width, image_height);
    }
    if (!_params._scene_file.empty()) {
        render_frame(pixels, image_width, image_height, cam, _world.primitives[0], _world.lights[0]);
        render_image(pixels, image_width, image_height);
    }
    delete[] pixels;
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
