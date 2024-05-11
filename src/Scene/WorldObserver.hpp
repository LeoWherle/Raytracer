

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
    WorldObserver(const std::vector<std::string> &files);

    ~WorldObserver() = default;

public:
    bool update(const std::vector<std::string> &files);

private:
    std::map<std::string, std::time_t> fileModificationTimes;
};
