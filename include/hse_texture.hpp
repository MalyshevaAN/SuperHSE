#ifndef HSE_TEXTURE_HPP
#define HSE_TEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace super_hse{
    void get_texture_from_file(std::string filename, sf::Texture &texture);
}

#endif
