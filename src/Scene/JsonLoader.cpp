/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** JsonLoader
*/

#include <fstream>
#include "JsonLoader.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

void JsonLoader::load(const std::string &filename)
{
    std::cout << "\e[1;35mLoading scene: " << filename << "\e[0m" << std::endl;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("\e[1;31mCould not open file + " + filename + "\e[0m");
    }
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(file, pt);
    json = pt;
    file.close();
}