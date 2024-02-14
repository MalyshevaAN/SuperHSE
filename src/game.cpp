#include "game.hpp"
#include <memory>
#include "scene.hpp"

namespace super_hse {

void Game::run() {
    sceneManager.changeScene(std::make_unique<MainMenuScene>());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            sceneManager.handleInput(event);
        }
        sceneManager.update();
        sceneManager.draw(window);
    }
}

}  // namespace super_hse
