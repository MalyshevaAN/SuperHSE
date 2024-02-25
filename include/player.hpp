#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

namespace super_hse {

struct Position {
    int x;
    int y;
};

class Player {
private:
    sf::Texture playerPicture;
    sf::Sprite sprite;
    Position position = {10, 10};

public:
    Player();
    void update();
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event &event);
    void move(int dx, int dy);
};

}  // namespace super_hse

#endif  // PLAYER_HPP_