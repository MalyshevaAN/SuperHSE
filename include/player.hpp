#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

namespace super_hse {

struct Position {
    float x;
    float y;
};

enum class PlayerState { STAND, WALK_LEFT, WALK_RIGHT, JUMP };

class Player {
private:
    sf::Texture playerPicture;
    sf::Sprite sprite;

    Position position = {200, 10};
    const float speed = 70.f;
    PlayerState state = PlayerState::STAND;

    float currentFrameColumn = 0;
    int currentFrameRow = 11;
    int totalFrames = 6;
    const int frameWidth = 64;
    const int frameHeight = 64;
    const float frameSpeed = 0.008;

public:
    Player();
    void update(const sf::Time &dTime);
    void draw(sf::RenderWindow &window);
    void handleInput(const sf::Event &event);
    void move(int dx, int dy);
    sf::FloatRect getCollider();
    sf::Vector2f calcMovement(const sf::Time &dTime);
    static const int start_position_x = 200;
    static const int start_position_y = 10;

    float getSpeed() const {
        return speed;
    }

    Position get_position();
    bool isGrounded = false;
};

}  // namespace super_hse

#endif  // PLAYER_HPP_
