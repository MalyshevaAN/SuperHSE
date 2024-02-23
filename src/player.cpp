// NOLINTNEXTLINE [clang-diagnostic-error]
#include "player.hpp"
#include <iostream>


namespace super_hse {

Player::Player() {
    if (!playerPicture.loadFromFile("../assets/images/man_walk.png")) {
        std::cerr << "Error loading man_walk.png\n";
    }
    std::cout << "Player created\n";
    sprite.setTexture(playerPicture);
    sprite.setPosition(10, 10);
}

void Player::update(sf::Time dTime) {
    // обрабатываем передвижение персонажа
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed;
        state = PlayerState::WALK_LEFT;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed;
        state = PlayerState::WALK_RIGHT;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed;

    } else {
        state = PlayerState::STAND;
    }
    movement *= dTime.asSeconds();
    move(movement.x, movement.y);

    // грузим следующий фрейм
    if (state == PlayerState::WALK_LEFT || state == PlayerState::WALK_RIGHT) {
        currentFrame += 0.008 * dTime.asMilliseconds();
        if (currentFrame > totalFrames) {
            currentFrame -= totalFrames;
        }
        sprite.setTextureRect(sf::IntRect(
            frameWidth * int(currentFrame), 0, frameWidth, frameHeight
        ));
        
    } else {
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    }
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
