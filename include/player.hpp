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
    float speed = 80.f;
    PlayerState state = PlayerState::STAND;
    
    float currentFrame = 0;
    int totalFrames = 6;
    int frameWidth = 48;
    int frameHeight = 54;

public:
    Player();
    void update(const sf::Time &dTime);
    void draw(sf::RenderWindow &window);
    void handleInput(const sf::Event &event);
    void move(int dx, int dy);
    sf::FloatRect getCollider();
    sf::Vector2f calcMovement(const sf::Time &dTime);

    float getSpeed() const { return speed; }
};

}  // namespace super_hse

#endif  // PLAYER_HPP_