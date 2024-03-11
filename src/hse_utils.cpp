#include "hse_utils.hpp"
#include <filesystem>
#include <iostream>

namespace super_hse {
void get_texture_from_file(std::string filename, sf::Texture& texture){
    std::filesystem::path p = std::filesystem::current_path();
    std::string texture_path = p.parent_path().string() + "/assets/images/" + filename;

    if (!texture.loadFromFile(texture_path)){
        std::cerr << "Error loading texture file " << filename << '\n';
    }
}
}
