/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** ConeFactory
*/

#pragma once

#include "Primitives/Cone.hpp"
#include "Factories/Math/Point3DFactory.hpp"
#include "Factories/Math/Vector3DFactory.hpp"
#include "Factories/MaterialFactory.hpp"
#include <list>
#include <boost/property_tree/ptree.hpp>

class ConeFactory : public Point3DFactory, public Vector3DFactory, public MaterialFactory {
    public:
        ConeFactory() = default;
        ~ConeFactory() = default;

        std::unique_ptr<Cone> createCone(const boost::property_tree::ptree &cone) const;


    private:
        const std::list<std::string> valid_transformations = {
            "translation",
            "rotation"
        };
};
