#include <game.hpp>

namespace super_hse {

Game::Game() {
    window.create(sf::VideoMode(640, 480, 32), "SFML Window");
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }  
}

} // namespace super_hse
