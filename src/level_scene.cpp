#include <memory>
#include "scene.hpp"
#include "Level.hpp"
#include <LDtkLoader/Project.hpp>
#include <string>
#include "TileMap.hpp"
#include <iostream>

namespace super_hse {

LevelScene::LevelScene() {
    player = Player();
    Level level;
    ldtk::Project project;
    std::string ldtk_filename = "../source/first_level2.ldtk";
    try {
        project.loadFromFile(ldtk_filename);
        std::cout << "LDtk World \"" << project.getFilePath() << "\" was loaded successfully." << std::endl;
    }
    catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
    level.init(project);
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
    //level.update() - пока нет
}

void LevelScene::draw(sf::RenderWindow &window) { // вот тут кринж, по другому пока не получилось, поэтому оно каждый раз занова карту загружает
    ldtk::Project project;                       // что плохо, но по другому оно почему то не видит уже загруженные слои, в чем трабла я пока не поняла
    std::string ldtk_filename = "../source/first_level2.ldtk"; // делать статическим пока тоже не вариант, у нас же много уровней будет. короче, разберусь
    try {
        project.loadFromFile(ldtk_filename);
        std::cout << "LDtk World \"" << project.getFilePath() << "\" was loaded successfully." << std::endl;
    }
    catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
    level.init(project);
    window.clear();
    player.draw(window);
    level.render(window);
    window.display();
}

}  // namespace super_hse
