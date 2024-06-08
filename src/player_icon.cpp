#ifndef PLAYER_ICON_CPP
#define PLAYER_ICON_CPP
#include "player_icon.hpp"
#include "hse_utils.hpp"
#include "sql.hpp"

namespace super_hse {
Player_icon::Player_icon() = default;

void Player_icon::update(float x, float y, int skin_id, int col, int row) {
    position.x = x;
    position.y = y;
    currentFrameColumn = col;
    currentFrameRow = row;
    if (!get_texture) {
        try {
            const char *skinPath = getSkinPath(skin_id).c_str();
            get_texture_from_file(skinPath, playerIconPicture);
            sprite.setTexture(playerIconPicture);
            get_texture = true;
        } catch (...) {
        }
    }
};

void Player_icon::changePos() {
    sprite.setTextureRect(
        sf::IntRect(frameWidth * currentFrameColumn, currentFrameRow * frameHeight, frameWidth, frameHeight)
    );
    sprite.setPosition(position.x - 23, position.y - 10);
    sprite.setColor(sf::Color(255, 255, 255, 128));
}

void Player_icon::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

}  // namespace super_hse

#endif
