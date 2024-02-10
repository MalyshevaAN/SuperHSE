#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace super_hse {

class Game {
private:
    sf::RenderWindow window;

public:
    Game();
    void run();
};

}  // namespace super_hse

#endif // GAME_HPP_