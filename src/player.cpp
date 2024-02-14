// NOLINTNEXTLINE [clang-diagnostic-error]
#include "player.hpp"

namespace super_hse {

Player::Player() {
    if (!playerPicture.loadFromFile("../assets/images/ryan-stand.png")) {
        std::cerr << "Error loading level_map.png\n";
    }
    sprite.setTexture(playerPicture);
    // тут инициализируем все что нужно в этой сцене
    sprite.setPosition(10, 10);
}

void Player::update() {}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Player::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
            move(5, 0);
        } else if (event.key.code == sf::Keyboard::Left) {
            move(-5, 0);
        } else if (event.key.code == sf::Keyboard::Up) {
            move(0, -5);
        } else if (event.key.code == sf::Keyboard::Down) {
            move(0, 5);
        }
    }
}

void Player::move(int dx, int dy) {
    sprite.move(dx, dy);
    sprite.setPosition(sprite.getPosition().x + dx, sprite.getPosition().y + dy);
}

}  // namespace super_hse
