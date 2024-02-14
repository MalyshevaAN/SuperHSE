#include <memory>
#include "scene.hpp"

namespace super_hse {

LevelScene::LevelScene() {
    player = Player();

}

void LevelScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::L) {
            SceneManager::changeScene(std::make_unique<LevelMapScene>());
            return;
        } else if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }
    player.handleInput(event);
}

void LevelScene::update() {
}

void LevelScene::draw(sf::RenderWindow &window) {
    window.clear();
    player.draw(window);
    window.display();
}

}  // namespace super_hse