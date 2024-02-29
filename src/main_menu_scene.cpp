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

void MainMenuScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<LevelMapScene>());
            return;
        }
    }
}

void MainMenuScene::update(sf::Time &dTime) {
}

void MainMenuScene::draw(sf::RenderWindow &window) {
    window.clear();
    window.draw(label);
    window.display();
}

}  // namespace super_hse
