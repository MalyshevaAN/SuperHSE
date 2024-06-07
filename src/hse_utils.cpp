#include "hse_utils.hpp"
#include <filesystem>
#include <iostream>
#include "game.hpp"
#include "sql.hpp"

namespace super_hse {

bool is_level_available(int num) {
    return isLevelAvailable(Game::player_id, num);
}

// void get_texture_from_file(std::string filename, sf::Texture &texture) {
//     const std::filesystem::path p = std::filesystem::current_path();
//     const std::string texture_path =
//         p.parent_path().string() + "/assets/images/" + filename;

//     if (!texture.loadFromFile(texture_path)) {
//         // std::cerr << "Error loading texture file " << filename << '\n';
//         throw textureException(filename);
//     }
// }

}  // namespace super_hse
