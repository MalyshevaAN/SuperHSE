#ifndef SKIN_ICON_HPP
#define SKIN_ICON_HPP

#include <SFML/Graphics.hpp>

namespace super_hse {
struct skinIcon {
    sf::Sprite skinIconSprite;
    sf::Texture skinIconTextureAvailable;
    sf::Texture skinIconTextureUnavailable;
    sf::Texture skinIconTextureCurrent;
    bool available = false;
    bool current = false;
    int number;

    skinIcon() = default;
    skinIcon(int num);
};
}  // namespace super_hse

#endif
