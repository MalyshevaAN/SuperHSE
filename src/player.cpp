// NOLINTNEXTLINE [clang-diagnostic-error]
#include <iostream>
#include "game.hpp"
#include "hse_utils.hpp"
#include "player.hpp"
#include "sql.hpp"

namespace super_hse {

const float GRAVITY = 70.f;

Player::Player() {
    const char *skinPath = getCurrentSkin(Game::player_id).c_str();
    get_texture_from_file(skinPath, playerPicture);
    sprite.setTexture(playerPicture);
    sprite.setPosition(220, 10);
}

sf::Vector2f Player::calcMovement(const sf::Time &dTime) {
    // вообще у плеера тоже должны быть стейты, чтобы например
    // он не мог прыгнуть, уже находясь в прыжке.

    sf::Vector2f movement(0.f, 0.f);
    // TODO: одновременное нажатие клавиш (прыжок + движение влево/вправо)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed;
        state = PlayerState::WALK_LEFT;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed;
        state = PlayerState::WALK_RIGHT;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        // TODO прыжок
        movement.y -= 2 * speed;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed;

    } else {
        state = PlayerState::STAND;
    }
    if (!isGrounded) {
        movement.y += GRAVITY;
    }
    movement *= dTime.asSeconds();
    return movement;
};

void Player::update(const sf::Time &dTime) {
    // грузим следующий фрейм
    if (state == PlayerState::WALK_LEFT || state == PlayerState::WALK_RIGHT) {
        currentFrameColumn += frameSpeed * dTime.asMilliseconds();
        if (currentFrameColumn > totalFrames) {
            currentFrameColumn -= totalFrames;
        }
        sprite.setTextureRect(sf::IntRect(
            frameWidth * int(currentFrameColumn), currentFrameRow * frameHeight,
            frameWidth, frameHeight
        ));

    } else {
        sprite.setTextureRect(sf::IntRect(
            0, currentFrameRow * frameHeight, frameWidth, frameHeight
        ));
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Player::handleInput(const sf::Event &event) {
}

void Player::move(int dx, int dy) {
    // TODO: разобраться с int/float
    sprite.move(dx, dy);
    sprite.setPosition(
        sprite.getPosition().x + dx, sprite.getPosition().y + dy
    );
}

sf::FloatRect Player::getCollider() {
    auto bounds = sprite.getGlobalBounds();
    sf::FloatRect rect;
    rect.width = bounds.width / 3;
    rect.left = bounds.left + rect.width;

    rect.top = bounds.top + 10;
    rect.height = bounds.height - 14;
    return rect;
}

}  // namespace super_hse
