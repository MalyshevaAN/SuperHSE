#include "scene.hpp"
#include <memory>

namespace super_hse {

void SceneManager::handleInput(sf::RenderWindow &window) {
    currentScene->handleInput(window);
}

std::unique_ptr<Scene> SceneManager::currentScene = nullptr;

void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
}

void SceneManager::update() {
    currentScene->update();
}

void SceneManager::draw(sf::RenderWindow &window) {
    currentScene->draw(window);
}

}  // namespace super_hse