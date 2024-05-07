/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Main.hpp"
#include "Materials/BaseMaterial.hpp"
#include "Materials/LightMaterial.hpp"
#include "Materials/MetalMaterial.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/Triangle.hpp"
#include "Scene/IncrementalImage.hpp"
#include "Scene/World.hpp"
#include "Scene/JsonLoader.hpp"
#include <boost/property_tree/ptree.hpp>
#include "Factories/WorldCreator.hpp"
#include "Factories/CameraFactory.hpp"

auto Main::arg_parse() -> bool
{
    try {
        _params.load(_ac, _av);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: " << _av[0] << " [scene file]" << std::endl;
        std::cerr << "Options:" << std::endl;
        std::cerr << "  -gui: Open a window to render the scene in real time" << std::endl;
        std::cerr << "  -o [outputfile]: Save the rendered image to the specified file (BMP, PPM or PNG)"
                  << std::endl;
        return false;
    }
    return true;
}

auto handle_events(sf::RenderWindow &window, Camera &cam) -> bool
{
    sf::Event event;
    constexpr auto movespeed = 0.5f;
    bool moved = false;
    while (window.pollEvent(event)) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
        switch (event.type) {

        case ::sf::Event::Resized:
            // Work in progress
            cam.image_width = event.size.width;
            cam.aspect_ratio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
            cam.update();
            break;
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            moved = true;
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                moved = false;
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
            case sf::Keyboard::Key::Add:
                cam.vfov -= 1;
                cam.update();
                break;
            case sf::Keyboard::Key::Subtract:
                cam.vfov += 1;
                cam.update();
                break;
            case sf::Keyboard::Key::J:
                cam.rotate(Vector3D(0, 1, 0), 0.1f);
                break;
            case sf::Keyboard::Key::K:
                cam.rotate(Vector3D(1, 0, 0), 0.1f);
                break;
            case sf::Keyboard::Key::L:
                cam.rotate(Vector3D(0, 0, 1), 0.1f);
                break;
            case sf::Keyboard::Key::U:
                cam.rotate(Vector3D(0, 1, 0), -0.1f);
                break;
            case sf::Keyboard::Key::I:
                cam.rotate(Vector3D(1, 0, 0), -0.1f);
                break;
            case sf::Keyboard::Key::O:
                cam.rotate(Vector3D(0, 0, 1), -0.1f);
                break;
            default:
                moved = false;
                break;
            }
        default:
            break;
        }
#pragma GCC diagnostic pop
    }
    return moved;
}

auto Main::render_real_time() -> void
{
    _camera.update();
    sf::RenderWindow window(sf::VideoMode(_camera.image_width, _camera.image_height), "Raytracer");

    IncrementalImage image;
    // check the time for rendering a frame
    sf::Clock clock;
    _camera.samples_per_pixel = 20;
    _camera.max_depth = 5;
    while (window.isOpen()) {
        if (handle_events(window, _camera)) {
            image.clear();
            _camera.max_depth = 5;
        }
        _camera.max_depth += 10;
        clock.restart();
        _camera.render<false>(_world, image);
        auto stop = clock.getElapsedTime();
        std::cout << "Rendering time: " << stop.asMilliseconds() << "ms" << std::endl;
        window.clear();
        window.draw(image);
        window.display();
    }
}

auto Main::run() -> int
{
    JsonLoader loader;
    CameraFactory camFactory;
    WorldCreator god;

    loader.load(_params._scene_file);
    _world = god.createWorld(loader.json.get_child("primitives"));
    _camera = camFactory.createCamera(loader.json.get_child("camera"));

    if (_params._gui) {
        render_real_time();
    }
    if (!_params._output_file.empty()) {
        _camera.render(_world, _image);
        _image.writeBMP(_params._output_file);
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
