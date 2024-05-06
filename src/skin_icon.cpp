#ifndef SKIN_ICON_CPP
#define SKIN_ICON_CPP

#include "skin_icon.hpp"
#include <SFML/Graphics.hpp>
#include "hse_utils.hpp"
#include "sql.hpp"
#include "game.hpp"

namespace super_hse {

skinIcon::skinIcon(int num) {
    available = isSkinAvailable(Game::player_id, num);
    current = static_cast<bool>(getCurrentSkinNum(Game::player_id) == num);
    number = num;

    get_texture_from_file("skin" +
        std::to_string(num) + "_available.png", skinIconTextureAvailable
    );
    get_texture_from_file("skin" +
        std::to_string(num) + "_unavailable.png", skinIconTextureUnavailable
    );
    get_texture_from_file("skin" +
        std::to_string(num) + "_current.png", skinIconTextureCurrent
    );
}

}  // namespace super_hse

#endif
