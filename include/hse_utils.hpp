#ifndef HSE_UTILS_HPP_
#define HSE_UTILS_HPP_
#include <SFML/Graphics.hpp>
#include <string>

namespace super_hse {

void get_texture_from_file(std::string filename, sf::Texture &texture);

bool is_level_available(int num);

static inline int all_levels = 2;

}  // namespace super_hse

#endif
