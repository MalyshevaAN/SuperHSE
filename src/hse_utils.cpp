#include "hse_utils.hpp"
#include "game.hpp"
#include "sql.hpp"
#include <filesystem>
#include <iostream>

namespace super_hse {

bool is_level_available(int num) {
    return isLevelAvailable(Game::player_id, num);
}

ldtkException::ldtkException(const std::string &message) : runtime_error(message){};
noSuchLdtkProject::noSuchLdtkProject(const std::string &projectName) : ldtkException("Cannot find \'" + projectName + "\'' project\n"){};
noSuchLevel::noSuchLevel(const std::string &levelName):ldtkException("Cannot find \'" + levelName + "\'' level\n"){};
noSuchLayer::noSuchLayer(const std::string &layerName):ldtkException("Cannot find \'" + layerName + "\'' layer in ldtk project\n"){};
noSuchDescriptionFile::noSuchDescriptionFile(const std::string &fileName) : ldtkException("Cannot find \'" + fileName + "\' description file\n"){}; 

textureException::textureException(const std::string &texture_name) : runtime_error("Cannot find texture named: " + texture_name){};

void get_texture_from_file(std::string filename, sf::Texture &texture) {
    const std::filesystem::path p = std::filesystem::current_path();
    const std::string texture_path =
        p.parent_path().string() + "/assets/images/" + filename;

    if (!texture.loadFromFile(texture_path)) {
        // std::cerr << "Error loading texture file " << filename << '\n';
        throw textureException(filename);
    }
}

}  // namespace super_hse
