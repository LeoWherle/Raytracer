

#pragma once

#include <chrono>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <sys/stat.h>
#include <thread>
#include <vector>

class WorldObserver {
public:
    WorldObserver(const std::vector<std::string> &files)
    {
        for (const auto &file : files) {
            std::cout << "Watching file " << file << std::endl;
            struct stat fileStat;
            if (stat(file.c_str(), &fileStat) == 0) {
                fileModificationTimes[file] = fileStat.st_mtime;
            } else {
                std::cerr << "Failed to get file status for " << file << std::endl;
            }
        }
    }

    ~WorldObserver() { }

public:
    bool update(const std::vector<std::string> &files)
    {
        bool modified = false;

        for (const auto &file : files) {
            if (!std::filesystem::exists(file)) {
                std::cerr << "File " << file << " does not exist anymore" << std::endl;
                continue;
            }

            struct stat fileStat;
            if (stat(file.c_str(), &fileStat) == 0) {
                std::time_t cftime = fileStat.st_mtime;
                if (fileModificationTimes[file] < cftime) {
                    fileModificationTimes[file] = cftime;
                    std::cout << "File " << file << " has been modified" << std::endl;
                    modified = true;
                }
            } else {
                std::cerr << "Failed to get file status for " << file << std::endl;
                continue;
            }
        }
        return modified;
    }

private:
    std::map<std::string, std::time_t> fileModificationTimes;
};
