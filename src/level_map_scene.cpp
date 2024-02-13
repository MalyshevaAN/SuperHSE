#include <memory>
#include "scene.hpp"

namespace super_hse {

LevelMapScene::LevelMapScene() {
    if (!levelMapPicture.loadFromFile("../assets/images/ryan2.png")) {
        std::cerr << "Error loading level_map.png\n";
    }
    label.setTexture(levelMapPicture);
    // тут инициализируем все что нужно в этой сцене
    label.setPosition(100, 100);
}

void LevelMapScene::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Num1) {
                SceneManager::changeScene(std::make_unique<LevelScene>());
                return;
            } else if (event.key.code == sf::Keyboard::M) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
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

}  // namespace super_hse