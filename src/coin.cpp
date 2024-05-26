#ifndef COIN_CPP_
#define COIN_CPP_

#include "coin.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace super_hse {

void coin::init() {
    coin::buffer.loadFromFile("../assets/audio/coin.wav");
    coin::sound.setBuffer(buffer);
}

void coin::setStatus(CoinStatus status_) {
    status = status_;
}

void coin::changeFrame(int frame) {
    coin_sprite.setTextureRect(sf::IntRect(
        static_cast<int>(frame) * coin::coinWidth, 0, coin::coinWidth,
        coin::coinHeight
    ));
}

void coin::disable() {
    if (status == CoinStatus::active) {
        coin::sound.play();
        status = CoinStatus::dieing;
    }
}

CoinStatus coin::get_status() {
    return status;
}

void coin::disappear() {
    if (height_change <= 3) {
        coin_sprite.setPosition(sf::Vector2f(
            coin_sprite.getPosition().x, coin_sprite.getPosition().y - 2
        ));
        height_change += 0.1;
    } else {
        status = CoinStatus::dead;
    }
}

}  // namespace super_hse

#endif
