#ifndef SKIN_ICON_HPP
#define SKIN_ICON_HPP

#include <SFML/Graphics.hpp>

namespace super_hse {
struct skinIcon {
    sf::Sprite skinIconSprite;
    sf::Texture skinIconTextureAvailable;
    sf::Texture skinIconTextureUnavailable;
    sf::Texture skinIconTextureCurrent;

    sf::Sprite HSEcoinSprite;
    sf::Texture HSEcoinTexture;
    sf::Text skinCost;

    bool available = false;
    bool current = false;
    int number;
    int cost;

    skinIcon() = default;
    skinIcon(int num);
};
}  // namespace super_hse

#endif
