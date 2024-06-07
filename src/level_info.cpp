#ifndef LEVEL_INFO_CPP
#define LEVEL_INFO_CPP

#include "level_info.hpp"
#include <filesystem>
#include <fstream>
#include "hse_utils.hpp"

namespace super_hse {
LevelInfo::LevelInfo(std::string file) {
    std::string line;
    std::ifstream in(file);
    if (in.is_open()) {
        std::getline(in, line);
        filename = line.substr(0, line.size());
        std::getline(in, line);
        std::getline(in, line);
        while (!line.empty()) {
            tileLayerName.push_back(line);
            std::getline(in, line);
        }
        std::getline(in, line);
        while (!line.empty()) {
            entityLayerName.push_back(line);
            std::getline(in, line);
        }
        std::getline(in, line);
        while (!line.empty()) {
            colliderName.push_back(line);
            std::getline(in, line);
        }
    } else {
        throw noSuchDescriptionFile(file);
    }
}

LevelsStorage::LevelsStorage() {
    std::filesystem::path p(std::filesystem::current_path());
    auto level1 = std::make_unique<LevelInfo>(
        p.parent_path().string() + "/assets/files/level2.txt"
    );

    auto level2 = std::make_unique<LevelInfo>(
        p.parent_path().string() + "/assets/files/level3.txt"
    );
    storage.push_back(std::move(level1));
    storage.push_back(std::move(level2));
}
}  // namespace super_hse

#endif
