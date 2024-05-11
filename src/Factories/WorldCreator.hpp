/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** WorldCreator
*/

#pragma once

#include "Primitives/ConeFactory.hpp"
#include "Primitives/CylinderFactory.hpp"
#include "Primitives/ObjFactory.hpp"
#include "Primitives/PlaneFactory.hpp"
#include "Primitives/SphereFactory.hpp"
#include "Primitives/TriangleFactory.hpp"
#include "Scene/JsonLoader.hpp"
#include "Scene/World.hpp"
#include "Scene/WorldObserver.hpp"
#include "Camera.hpp"
#include "CameraFactory.hpp"
#include <boost/property_tree/ptree.hpp>

class WorldCreator : public SphereFactory,
                     public TriangleFactory,
                     public PlaneFactory,
                     public ObjFactory,
                     public ConeFactory,
                     public CylinderFactory {
public:
    WorldCreator() = default;
    ~WorldCreator() = default;

    void createWorld(World &world, const boost::property_tree::ptree &pt);
    void destroyWorld(World &world);

    bool update_on_file_change(World &world, Camera &cam)
    {
        bool modified = false;
        for (auto &obs : observers) {
            modified |= obs->update(opened_files);
        }
        if (modified) {
            JsonLoader jsonLoader;
            try {
                jsonLoader.load(_rootfile);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            destroyWorld(world);
            createWorld(world, jsonLoader.json);
            cam = CameraFactory::createCamera(jsonLoader.json.get_child("camera"));
            cam.update();
        }
        return modified;
    }

    void attach(WorldObserver *observer) { observers.push_back(observer); }
    void detach(WorldObserver *observer)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    std::vector<std::string> opened_files;
    std::string _rootfile;

    std::vector<WorldObserver *> observers;
};
