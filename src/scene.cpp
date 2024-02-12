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

MainMenuScene::MainMenuScene() {
    if (!mainMenuLabel.loadFromFile("../assets/images/ryan.png")) {
        std::cerr << "Error loading ryan.png\n";
    }
    label.setTexture(mainMenuLabel);
    // тут инициализируем все что нужно в этой сцене
    label.setPosition(100, 100);
    
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
    window.clear();

    window.draw(label);
    window.display();
}

void LevelMapScene::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void LevelMapScene::update() {
}

void LevelMapScene::draw(sf::RenderWindow &window) {
    window.clear();
    window.display();
}

} // namespace super_hse