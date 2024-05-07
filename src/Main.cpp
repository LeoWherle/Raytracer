/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** Main
*/

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Factories/CameraFactory.hpp"
#include "Factories/WorldCreator.hpp"
#include "Main.hpp"
#include "Materials/BaseMaterial.hpp"
#include "Materials/LightMaterial.hpp"
#include "Materials/MetalMaterial.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/Triangle.hpp"
#include "Scene/IncrementalImage.hpp"
#include "Scene/JsonLoader.hpp"
#include "Scene/World.hpp"
#include <boost/property_tree/ptree.hpp>

auto Main::arg_parse() -> bool
{
    try {
        _params.load(_ac, _av);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: " << _av[0] << " [scene file]" << std::endl;
        std::cerr << "Options:" << std::endl;
        std::cerr << "  -gui: Open a window to render the scene in real time" << std::endl;
        std::cerr << "  -o [outputfile]: Save the rendered image to the specified file (BMP, PPM, PNG, TGA, "
                     "JPG), default is output.bmp. If -gui is set, the image will be saved when the window "
                     "is closed."
                     "The file extension will determine the format."
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
    sf::Text text;
    sf::Font font;
    font.loadFromFile("assets/font/BebasNeue-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    text.setString("Sample per pixel: " + std::to_string(_image.get_sample_count()));
    sf::Clock clock;
    _camera.samples_per_pixel = 10;
    _camera.max_depth = 5;

    double total_time = 0;
    auto old_elapsed = clock.getElapsedTime();
    auto elapsed = clock.getElapsedTime();

    while (window.isOpen()) {
        if (handle_events(window, _camera)) {
            _image.clear();
            _camera.max_depth = 5;
            clock.restart();
        }
        _camera.max_depth += 1;
        _camera.render<false>(_world, _image);

        // prepare info display
        old_elapsed = elapsed;
        elapsed = clock.getElapsedTime();
        total_time = elapsed.asMilliseconds() - old_elapsed.asMilliseconds();
        std::cout << "Frame Rendering time: " << total_time << "ms" << std::endl;
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2);
        stream << "Render Time: " << (static_cast<double>(elapsed.asMilliseconds()) / 1000) << "s"
               << "\n";
        stream << "Sample per pixel: " << _image.get_sample_count() << "\n";
        stream << "Depth: " << _camera.max_depth << "\n";
        text.setString(stream.str());

        window.clear();
        window.draw(_image);
        window.draw(text);
        window.display();
    }
}

auto Main::run() -> int
{
    JsonLoader loader;
    CameraFactory camFactory;
    WorldCreator god;

    loader.load(_params._scene_file);
    god.createWorld(_world, loader.json.get_child("primitives"));
    _camera = camFactory.createCamera(loader.json.get_child("camera"));

    if (_params._gui) {
        render_real_time();
    }
    if (!_params._output_file.empty()) {
        if (!_params._gui) {
            _camera.render(_world, _image);
        }
        _image.save(_params._output_file);
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
