#include "game.hpp"
#include <memory>
#include "scene.hpp"


#include <iostream>

namespace super_hse {

int Game::windowWidth = 960;
int Game::windowHeight = 640;

int Game::defaultWindowWidth = 960;
int Game::defaultWindowHeight = 640;

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

                if (isFullScreen) {
                    windowWidth = defaultWindowWidth;
                    windowHeight = defaultWindowHeight;
                    window.create(sf::VideoMode(windowWidth, windowHeight, 32), "Super HSE", sf::Style::Default);

                } else {
                    window.create(sf::VideoMode::getDesktopMode(), "Super HSE", sf::Style::Fullscreen);
                    windowWidth = window.getSize().x;
                    windowHeight = window.getSize().y;
                }

                isFullScreen = !isFullScreen;
            }
            SceneManager::handleInput(event);
        }
        sf::Time dTime = clock.restart();
        SceneManager::update(dTime);
        SceneManager::draw(window);
    }
}

}  // namespace super_hse