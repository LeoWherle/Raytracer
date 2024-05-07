/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** JsonLoader
*/

#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include "JsonLoader.hpp"

void JsonLoader::load(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(file, pt);
    json = pt;
}