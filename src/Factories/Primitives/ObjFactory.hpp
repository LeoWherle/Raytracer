/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-leo.wehrle [WSL: Ubuntu]
** File description:
** ObjFactory
*/

#pragma once

#include "Factories/MaterialFactory.hpp"
#include "Factories/Math/Point3DFactory.hpp"
#include "Primitives/Object.hpp"
#include <boost/property_tree/ptree.hpp>

class ObjFactory : public Point3DFactory, public MaterialFactory {
public:
    ObjFactory() = default;
    ~ObjFactory() = default;

    std::unique_ptr<Object> createObj(const boost::property_tree::ptree &pt) const;

protected:
private:
};
