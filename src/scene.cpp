#include <memory>
#include "scene.hpp"

namespace super_hse {

bool SceneManager::needToChangeScene = false;
SceneType SceneManager::nextSceneType = SceneType::NONE;

void SceneManager::handleInput(sf::RenderWindow &window) {
    currentScene->handleInput(window);
}

void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
}

void SceneManager::update() {
    if (!needToChangeScene) {
        currentScene->update(); 
        return;
    }

    needToChangeScene = false;
    switch (nextSceneType) {
        case SceneType::MAIN_MENU:
            changeScene(std::make_unique<MainMenuScene>());
            break;
        case SceneType::LEVEL_MAP:
            changeScene(std::make_unique<LevelMapScene>());
            break;
        default:
            break;
    }
}

void SceneManager::draw(sf::RenderWindow &window) {
    currentScene->draw(window);
}

LevelMapScene::LevelMapScene() {
    if (!levelMapPicture.loadFromFile("../assets/images/ryan2.png")) {
        std::cerr << "Error loading level_map.png\n";
    }
    label.setTexture(levelMapPicture);
    // тут инициализируем все что нужно в этой сцене
    label.setPosition(100, 100);
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
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                SceneManager::needToChangeScene = true;
                SceneManager::nextSceneType = SceneType::LEVEL_MAP;
            }
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

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                SceneManager::needToChangeScene = true;
                SceneManager::nextSceneType = SceneType::MAIN_MENU;
            }
        }
    }
}

void LevelMapScene::update() {
}

void LevelMapScene::draw(sf::RenderWindow &window) {
    window.clear();
    window.draw(label);
    window.display();
}

} // namespace super_hse