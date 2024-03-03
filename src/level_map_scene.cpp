#include <memory>
#include "scene.hpp"
#include "level_map_scene.hpp"

namespace super_hse {

LevelMapScene::LevelMapScene() {
    if (!buttonLevel1Picture.loadFromFile("../assets/images/button_level_1.png")) {
        std::cerr << "Error loading level_map.png\n";
    }
    buttonLevel1.setTexture(buttonLevel1Picture);
    buttonLevel1.setPosition(100, 100);
}

void LevelMapScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            SceneManager::changeScene(std::make_unique<LevelScene>(
                "../assets/tilemaps/first_level2.ldtk"
            ));
            return;
        } else if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (buttonLevel1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                SceneManager::changeScene(std::make_unique<LevelScene>(
                    "../assets/tilemaps/first_level2.ldtk"
                ));
                return;
            }
        }
    }
}

void LevelMapScene::update(sf::Time &dTime) {
}

void LevelMapScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(buttonLevel1);
    window.display();
}

}  // namespace super_hse
