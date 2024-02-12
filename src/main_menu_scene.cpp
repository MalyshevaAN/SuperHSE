#include <memory>
#include "scene.hpp"

namespace super_hse {

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
                SceneManager::changeScene(std::make_unique<LevelMapScene>());
                return;
                // SceneManager::needToChangeScene = true;
                // SceneManager::nextSceneType = SceneType::LEVEL_MAP;
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

}  // namespace super_hse