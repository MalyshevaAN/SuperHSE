#include "scene.hpp"
#include <memory>
#include "level_map_scene.hpp"

namespace super_hse {

void SceneManager::handleInput(sf::Event &event) {
    currentScene->handleInput(event);
}

std::unique_ptr<Scene> SceneManager::currentScene = nullptr;

void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
}

void SceneManager::update(sf::Time &dTime) {
    currentScene->update(dTime);
}

void SceneManager::draw(sf::RenderWindow &window) {
    currentScene->draw(window);
}

void SceneManager::updateSceneSize() {
    currentScene->updateSceneSize();
}

}  // namespace super_hse
