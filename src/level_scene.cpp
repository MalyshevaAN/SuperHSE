#include <memory>
#include "scene.hpp"

namespace super_hse {

LevelScene::LevelScene() {
    if (!levelPicture.loadFromFile("../assets/images/ryan3.png")) {
        std::cerr << "Error loading level_map.png\n";
    }
    label.setTexture(levelPicture);
    // тут инициализируем все что нужно в этой сцене
    label.setPosition(10, 10);
}

void LevelScene::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::L) {
                SceneManager::changeScene(std::make_unique<LevelMapScene>());
                return;
            } else if (event.key.code == sf::Keyboard::M) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
        }
    }
}

void LevelScene::update() {
}

void LevelScene::draw(sf::RenderWindow &window) {
    window.clear();
    window.draw(label);
    window.display();
}

}  // namespace super_hse