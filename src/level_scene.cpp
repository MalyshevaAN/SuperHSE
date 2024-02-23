#include <LDtkLoader/Project.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "Level.hpp"
#include "TileMap.hpp"
#include "scene.hpp"

namespace super_hse {

LevelScene::LevelScene(int levelN) {
    levelNumber = levelN;
    player = Player();
    std::string filename = storage.storage.at(levelNumber)->filename;
    level.ldtk_filename = storage.storage.at(levelNumber)->filename;
    level.project.loadFromFile(filename);
    level.init(
        storage.storage.at(levelNumber)->tileLayerName,
        storage.storage.at(levelNumber)->entityLayerName,
        storage.storage.at(levelNumber)->colliderName
    );
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
    level.render(window, storage.storage.at(levelNumber)->tileLayerName);
    player.draw(window);
    window.display();
}

}  // namespace super_hse
