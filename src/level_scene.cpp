#include <LDtkLoader/Project.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "Level.hpp"
#include "TileMap.hpp"
#include "scene.hpp"

namespace super_hse {

LevelScene::LevelScene(std::string filename) {
    player = Player();
    level.ldtk_filename = filename;
    level.project.loadFromFile(filename);
    level.init();
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
    // level.update() - пока нет
}

void LevelScene::draw(sf::RenderWindow &window) {
    window.clear();
    player.draw(window);
    level.render(window);
    window.display();
}

}  // namespace super_hse
