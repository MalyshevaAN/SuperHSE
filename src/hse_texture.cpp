#ifndef HSE_TEXTURE_CPP
#define HSE_TEXTURE_CPP

#include "hse_texture.hpp"
#include <filesystem>
#include "hse_exceptions.hpp"
#include <iostream>

namespace super_hse{
void get_texture_from_file(std::string filename, sf::Texture &texture) {
    const std::filesystem::path p = std::filesystem::current_path();
    const std::string texture_path =
        p.parent_path().string() + "/assets/images/" + filename;

    if (!texture.loadFromFile(texture_path)) {
        std::cerr << "Error loading texture file " << filename << '\n';
        throw textureException(filename);
    }
}

}

#endif