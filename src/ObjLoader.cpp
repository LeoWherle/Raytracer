/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** ObjLoader
*/

#include "ObjLoader.hpp"
#include "Primitives/TriangleObj.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

// f 390//1621 1928//1615 1310//1622
auto ObjLoader::parse_index(const std::string &line) -> std::array<int, 3>
{
    std::array<int, 3> index;

    std::string vertex1, vertex2, vertex3;
    std::istringstream ss(line.substr(2));
    ss >> vertex1 >> vertex2 >> vertex3;

    index[0] = std::stoi(vertex1);
    index[1] = std::stoi(vertex2);
    index[2] = std::stoi(vertex3);

    return index;
}

auto ObjLoader::parse_vertex(const std::string &line) -> Point3D
{
    Point3D vertex;

    std::string x, y, z;
    std::istringstream ss(line.substr(2));
    ss >> x >> y >> z;

    vertex._x = std::stof(x);
    vertex._y = std::stof(y);
    vertex._z = std::stof(z);

    return vertex;
}

auto ObjLoader::parse_normal(const std::string &line) -> Vector3D
{
    Vector3D normal;

    std::string x, y, z;
    std::istringstream ss(line.substr(3));
    ss >> x >> y >> z;

    normal._x = std::stof(x);
    normal._y = std::stof(y);
    normal._z = std::stof(z);

    return normal;
}

auto ObjLoader::load(const std::string &filename, const Point3D &origin, float scale, const IMaterial *material)
    -> std::unique_ptr<Object>
{
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    std::vector<Point3D> vertices;
    std::vector<Vector3D> normals;
    std::vector<std::array<int, 3>> indices;

    std::string line;
    while (std::getline(file, line)) {
        // skip comments
        if (line[0] == '#' || line.empty()) {
            continue;
        }
        if (line[0] == 'v' && line[1] == ' ') {
            vertices.push_back(parse_vertex(line));
        } else if (line[0] == 'v' && line[1] == 'n') {
            normals.push_back(parse_normal(line));
        } else if (line[0] == 'f') {
            indices.push_back(parse_index(line));
        }
    }

    if (vertices.empty() || indices.empty() || normals.empty()) {
        throw std::runtime_error("Invalid object file: " + filename);
    }
    std::cout << "Object loaded: " << filename << std::endl
              << "\tnumber of vertices: " << vertices.size() << std::endl
              << "\tnumber of normals: " << normals.size() << std::endl
              << "\tnumber of indices: " << indices.size() << std::endl;
    auto object = std::make_unique<Object>(origin, scale, material);

    for (size_t i = 0; i < indices.size(); i++) {
        for (int j = 0; j < 3; j++) {
            if (indices[i][j] < 0 || static_cast<size_t>(indices[i][j]) > vertices.size() || static_cast<size_t>(indices[i][j]) > normals.size()) {
                throw std::runtime_error("Index out of bounds: " + std::to_string(indices[i][j]));
            }
        }
        auto triangle = std::make_unique<TriangleObj>(
            std::array<Point3D, 3> {
                vertices[indices[i][0] - 1] * scale + origin, //
                vertices[indices[i][1] - 1] * scale + origin, //
                vertices[indices[i][2] - 1] * scale + origin //
            },
            std::array<Vector3D, 3> {
                normals[indices[i][0] - 1], normals[indices[i][1] - 1], normals[indices[i][2] - 1]
            },
            material
        );
        object->addTriangle(std::move(triangle));
    }
    object->build();
    return object;
}