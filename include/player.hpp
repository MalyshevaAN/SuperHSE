#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

namespace super_hse {

struct Position {
    int x;
    int y;
};

enum class PlayerState {
    STAND,
    WALK_LEFT,
    WALK_RIGHT,
    JUMP
};

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

    float getSpeed() const { return speed; }
    bool isGrounded = false;
};

}  // namespace super_hse

#endif  // PLAYER_HPP_