// NOLINTNEXTLINE [clang-diagnostic-error]
#include "player.hpp"
#include <iostream>


namespace super_hse {

Player::Player() {
    if (!playerPicture.loadFromFile("../assets/images/ryan-stand.png")) {
        std::cerr << "Error loading level_map.png\n";
    }
    sprite.setTexture(playerPicture);

    // тут инициализируем все что нужно в этой сцене
    sprite.setPosition(10, 10);
}

void Player::update(sf::Time dTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed;
    }
    movement *= dTime.asSeconds();
    std::cout << movement.x << " " << movement.y << std::endl;
    move(movement.x, movement.y);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Player::handleInput(sf::Event &event) {

}

void Player::move(int dx, int dy) {
    // TODO:
    // разобраться с int/float
    sprite.move(dx, dy);
    sprite.setPosition(
        sprite.getPosition().x + dx, sprite.getPosition().y + dy
    );
}

sf::FloatRect Player::getCollider() {
    auto bounds = sprite.getGlobalBounds();
    sf::FloatRect rect;
    rect.left = bounds.left;
    rect.width = bounds.width;
    rect.top = bounds.top + bounds.height / 2;
    rect.height = bounds.height / 2;
    return rect;
}

}  // namespace super_hse
