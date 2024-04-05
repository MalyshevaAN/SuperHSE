#ifndef LEVEL_ICON_HPP
#define LEVEL_ICON_HPP

#include <SFML/Graphics.hpp>

namespace super_hse {
struct levelIcon {
    sf::Sprite levelIconSprite;
    sf::Texture levelIconTextureAvailable;
    sf::Texture levelIconTextureUnavailable;
    bool available = false;
    int number;

    levelIcon() = default;
    levelIcon(int num);
};
}  // namespace super_hse

#endif
