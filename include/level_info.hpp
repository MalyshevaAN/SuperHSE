#ifndef LEVEL_INFO_HPP
#define LEVEL_INFO_HPP

#include <memory>
#include <string>
#include <vector>

namespace super_hse {
struct LevelInfo;

struct LevelsStorage {
    std::vector<std::unique_ptr<LevelInfo>> storage;

    LevelsStorage();
};

struct LevelInfo {
    std::string filename;
    std::vector<std::string> tileLayerName;
    std::vector<std::string> entityLayerName;
    std::vector<std::string> colliderName;

    LevelInfo() = default;

    LevelInfo(std::string file);

    friend LevelsStorage;
};

}  // namespace super_hse

#endif
