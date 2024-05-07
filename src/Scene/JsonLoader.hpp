/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** JsonLoader
*/

#pragma once
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <string>
#include <boost/property_tree/ptree.hpp>

class JsonLoader {
public:
    JsonLoader() = default;
    ~JsonLoader() = default;

    void load(const std::string &filename);

    boost::property_tree::ptree json;
};
