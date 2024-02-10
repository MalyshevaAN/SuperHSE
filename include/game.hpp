#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Game {
private:
    sf::RenderWindow window;

public:
    Game();
    void run();
};

#endif // GAME_HPP_
