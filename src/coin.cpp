#ifndef COIN_CPP_
#define COIN_CPP_

#include "coin.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace super_hse{

void coin::init(){
    coin::buffer.loadFromFile("../assets/audio/coin.wav");
    coin::sound.setBuffer(buffer);
}

void coin::change(int frame){
    entity_sprite.setTextureRect(sf::IntRect(
    static_cast<int>(frame) * coin::coinWidth, 0, coin::coinWidth,
    coin::coinHeight));
}

void coin::disable(){
    if (status == EntityStatus::ACTIVE){
        coin::sound.play();
        setStatus(EntityStatus::DIEING);
        // status = EntityStatus::DIEING;
    }
}


void coin::disappear(){
    if (height_change <= 3){
        entity_sprite.setPosition(sf::Vector2f(entity_sprite.getPosition().x, entity_sprite.getPosition().y - 2));
        height_change += 0.1;
    }else {
        setStatus(EntityStatus::DEAD);
        // status = EntityStatus::DEAD;
    }
}

void coin::unable(){
    
}

}


#endif
