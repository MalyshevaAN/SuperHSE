#include <memory>
#include "scene.hpp"
#include "game.hpp"

namespace super_hse {

void SceneManager::handleInput(sf::RenderWindow &window) {
    currentScene->handleInput(window);
}

void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
}

void SceneManager::update() {
    currentScene->update();
}

void SceneManager::draw(sf::RenderWindow &window) {
    currentScene->draw(window);
}

void MainMenuScene::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void MainMenuScene::update() {
}

void MainMenuScene::draw(sf::RenderWindow &window) {
}

} // namespace super_hse