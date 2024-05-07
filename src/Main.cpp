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
#include "Primitives/Triangle.hpp"
#include "Primitives/Sphere.hpp"
#include "Scene/IncrementalImage.hpp"
#include "Scene/World.hpp"
#include "Scene/JsonLoader.hpp"
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
    _camera.samples_per_pixel = 100;
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

static void WIPShereFactory(World &_world, JsonLoader &loader)
{
    for (boost::property_tree::ptree::value_type &sphere : loader.json.get_child("primitives").get_child("spheres")) {
        auto center = Point3D(
            sphere.second.get<float>("position.x"),
            sphere.second.get<float>("position.y"),
            sphere.second.get<float>("position.z")
        );
        auto color = Color(
            sphere.second.get<float>("material.color.r"),
            sphere.second.get<float>("material.color.g"),
            sphere.second.get<float>("material.color.b")
        );
        auto radius = sphere.second.get<float>("radius");
        auto material = sphere.second.get<std::string>("material.material");

        if (material == "LightMaterial") {
            _world.addPrimitive(std::make_shared<Sphere>(center, radius, std::make_shared<LightMaterial>(color)));
        } else if (material == "MetalMaterial") {
            auto fuzz = sphere.second.get<float>("material.fuzz");
            _world.addPrimitive(std::make_shared<Sphere>(center, radius, std::make_shared<MetalMaterial>(color, fuzz)));
        } else {
            _world.addPrimitive(std::make_shared<Sphere>(center, radius, std::make_shared<BaseMaterial>(color)));
        }
    }
}

static void WIPTriangleFactory(World &_world, JsonLoader &loader)
{
    std::vector<Point3D> vertices;
    for (boost::property_tree::ptree::value_type &triangle : loader.json.get_child("primitives").get_child("triangles")) {
        for (boost::property_tree::ptree::value_type &vectice : triangle.second.get_child("vertices")) {
            vertices.push_back(Point3D(
                vectice.second.get<float>("x"),
                vectice.second.get<float>("y"),
                vectice.second.get<float>("z")
            ));
        }
        if (vertices.size() != 3) {
            throw std::runtime_error("Triangle must have 3 vertices");
        }
        auto color = Color(
            triangle.second.get<float>("material.color.r"),
            triangle.second.get<float>("material.color.g"),
            triangle.second.get<float>("material.color.b")
        );
        auto material = triangle.second.get<std::string>("material.material");

        if (material == "LightMaterial") {
            _world.addPrimitive(std::make_shared<Triangle>(vertices[0], vertices[1], vertices[2], std::make_shared<LightMaterial>(color)));
        } else if (material == "MetalMaterial") {
            auto fuzz = triangle.second.get<float>("material.fuzz");
            _world.addPrimitive(std::make_shared<Triangle>(vertices[0], vertices[1], vertices[2], std::make_shared<MetalMaterial>(color, fuzz)));
        } else {
            _world.addPrimitive(std::make_shared<Triangle>(vertices[0], vertices[1], vertices[2], std::make_shared<BaseMaterial>(color)));
        }
    }
}

static void WIPPlaneFactory(World &_world, JsonLoader &loader)
{
    for (boost::property_tree::ptree::value_type &plane : loader.json.get_child("primitives").get_child("planes")) {
        auto origin = Point3D(
            plane.second.get<float>("position.x"),
            plane.second.get<float>("position.y"),
            plane.second.get<float>("position.z")
        );
        auto normal = Vector3D(
            plane.second.get<float>("normal.x"),
            plane.second.get<float>("normal.y"),
            plane.second.get<float>("normal.z")
        );
        auto color = Color(
            plane.second.get<float>("material.color.r"),
            plane.second.get<float>("material.color.g"),
            plane.second.get<float>("material.color.b")
        );
        auto material = plane.second.get<std::string>("material.material");

        if (material == "LightMaterial") {
            _world.addPrimitive(std::make_shared<Plane>(origin, normal, std::make_shared<LightMaterial>(color)));
        } else if (material == "MetalMaterial") {
            auto fuzz = plane.second.get<float>("material.fuzz");
            _world.addPrimitive(std::make_shared<Plane>(origin, normal, std::make_shared<MetalMaterial>(color, fuzz)));
        } else {
            _world.addPrimitive(std::make_shared<Plane>(origin, normal, std::make_shared<BaseMaterial>(color)));
        }
    }

}

auto Main::run() -> int
{
    JsonLoader loader;

    loader.load(_params._scene_file);
    
    WIPShereFactory(_world, loader);
    WIPTriangleFactory(_world, loader);
    WIPPlaneFactory(_world, loader);
    _camera.aspect_ratio = 16.0f / 9.0f;
    _camera.image_width = loader.json.get<int>("camera.resolution.width");
    _camera.samples_per_pixel = loader.json.get<int>("camera.RayPerPixel");
    _camera.max_depth = loader.json.get<int>("camera.MaxBounces");
    _camera.background._r = loader.json.get<float>("camera.BackgroundColor.r");
    _camera.background._g = loader.json.get<float>("camera.BackgroundColor.g");
    _camera.background._b = loader.json.get<float>("camera.BackgroundColor.b");

    _camera.vfov = loader.json.get<float>("camera.fieldOfView");
    _camera.origin._x = loader.json.get<float>("camera.position.x");
    _camera.origin._y = loader.json.get<float>("camera.position.y");
    _camera.origin._z = loader.json.get<float>("camera.position.z");
    _camera.lookat._x = loader.json.get<float>("camera.rotation.x");
    _camera.lookat._y = loader.json.get<float>("camera.rotation.y");
    _camera.lookat._z = loader.json.get<float>("camera.rotation.z");
    _camera.vup = Vector3D(0, 1, 0);

    _camera.defocus_angle = loader.json.get<float>("camera.DefocusAngle");

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
