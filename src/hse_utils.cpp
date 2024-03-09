#include "hse_utils.hpp"
#include <iostream>

namespace super_hse {
void get_texture_from_file(std::string file_name, sf::Texture& texture){
    if (!texture.loadFromFile(file_name)){
        std::cerr<<"Error loading texture file " << file_name << '\n';
    }
}
}
