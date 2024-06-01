#ifndef PLAYER_ICON_CPP
#define PLAYER_ICON_CPP
#include "player_icon.hpp"
#include "sql.hpp"
#include "hse_utils.hpp"

namespace super_hse{
Player_icon::Player_icon() = default;

void Player_icon::update(float x, float y, int skin_id, int col, int row){
    position.x = x;
    position.y = y;
    if (!get_texture){
        try{
            const char *skinPath = getCurrentSkin(3).c_str();
            get_texture_from_file(skinPath, playerIconPicture);
            sprite.setTexture(playerIconPicture);
            get_texture = true;
        }catch (...){

        }
    }
    currentFrameColumn = col;
    currentFrameRow = row;
};

void Player_icon::changePos(){
    sprite.setTextureRect(sf::IntRect(0, currentFrameRow * frameHeight, frameWidth, frameHeight));
    sprite.setPosition(position.x, position.y);
}

void Player_icon::draw(sf::RenderWindow &window){
    window.draw(sprite);
}

}


#endif
