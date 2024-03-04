#include "game.hpp"
#include <memory>
#include "scene.hpp"

namespace super_hse {

int Game::windowWidth = 960;
int Game::windowHeight = 640;

void Game::run() {
    SceneManager::changeScene(std::make_unique<MainMenuScene>());

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }
            SceneManager::handleInput(event);
        }
        sf::Time dTime = clock.restart();
        SceneManager::update(dTime);
        SceneManager::draw(window);
    }
}

}  // namespace super_hse
