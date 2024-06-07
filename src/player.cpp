// NOLINTNEXTLINE [clang-diagnostic-error]
#include "player.hpp"
#include <iostream>
#include "game.hpp"
#include "hse_utils.hpp"
#include "sql.hpp"

namespace super_hse {

const float GRAVITY = 450.f;
const float JUMP_SPEED = 380.f;

Player::Player() {
    const char *skinPath = getCurrentSkin(Game::player_id).c_str();
    get_texture_from_file(skinPath, playerPicture);
    sprite.setTexture(playerPicture);
    sprite.setPosition(200, 10);
    Player::buffer.loadFromFile("../assets/audio/death.wav");
    Player::sound.setBuffer(buffer);
}

sf::Vector2f Player::calcMovement(const sf::Time &dTime) {
    // вообще у плеера тоже должны быть стейты, чтобы например
    // он не мог прыгнуть, уже находясь в прыжке.

    sf::Vector2f movement(0.f, 0.f);
    // TODO: одновременное нажатие клавиш (прыжок + движение влево/вправо)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed;
        state = PlayerState::WALK_LEFT;
        currentFrameRow = 9;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed;
        state = PlayerState::WALK_RIGHT;
        currentFrameRow = 11;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        // TODO прыжок
        if (isGrounded) {
            verticalVelocity -= JUMP_SPEED;
            isGrounded = false;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed;

    } else {
        state = PlayerState::STAND;
        currentFrameRow = 10;
    }
    verticalVelocity += GRAVITY * dTime.asSeconds();
    if (isGrounded) {
        verticalVelocity = 0;
    }
    std::cout << verticalVelocity << "\n";
    movement.y += verticalVelocity;
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
    sprite.move(dx, dy);
    sprite.setPosition(
        sprite.getPosition().x , sprite.getPosition().y
    );
}

Position Player::get_position() {
    return {sprite.getPosition().x, sprite.getPosition().y};
}

void Player::lose_life() {
    Player::sound.play();
    active_lives--;
}

int Player::get_active_lives() {
    return active_lives;
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
