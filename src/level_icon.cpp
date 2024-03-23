#ifndef LEVEL_ICON_CPP
#define LEVEL_ICON_CPP

#include "level_icon.hpp"
#include "hse_utils.hpp"
#include <SFML/Graphics.hpp>

namespace super_hse{

levelIcon::levelIcon(int num){
    available = is_level_available(num);
    get_texture_from_file(std::to_string(num) + "_available.png", levelIconTextureAvailable);
    get_texture_from_file(std::to_string(num) + "_unavailable.png", levelIconTextureUnavailable);
    number = num;
}

}

#endif
