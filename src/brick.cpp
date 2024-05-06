#ifndef BRICK_CPP
#define BRICK_CPP

#include "hse_utils.hpp"
#include "brick.hpp"

namespace super_hse{
void brick::init(){
    get_texture_from_file("bricks.png", brickTexture);
    get_texture_from_file("floor.png", floorTexture);
}

brick::brick(int left, int top, int width, int height, const std::string textureName){
    brick_sprite.setPosition(left, top);
    if(textureName == "brick"){
        brick_sprite.setTexture(brickTexture);
    }else if (textureName == "floor"){
        brick_sprite.setTexture(floorTexture);
    }
    brick_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    brickRect = sf::FloatRect(left, top, width, height);
}

}

#endif
