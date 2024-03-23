#include "level_map_scene.hpp"
#include <filesystem>
#include <memory>
#include "hse_utils.hpp"
#include "level_scene.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"

namespace super_hse {

LevelMapScene::LevelMapScene() {
    get_texture_from_file("button_level_1.png", buttonLevel1Picture);

    buttonLevel1.setTexture(buttonLevel1Picture);
    buttonLevel1.setPosition(100, 100);
}

void LevelMapScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            SceneManager::changeScene(std::make_unique<LevelScene>(0));

            return;
        } else if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (buttonLevel1.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<LevelScene>(0));
                return;
            }
        }
    }
}

void LevelMapScene::update(sf::Time &dTime) {
}

void LevelMapScene::updateSceneSize() {
}

void LevelMapScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(buttonLevel1);
    window.display();
}

}  // namespace super_hse
