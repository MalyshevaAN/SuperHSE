#ifndef LEVEL_CPP_
#define LEVEL_CPP_

#include "Level.hpp"
#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "TileMap.hpp"

namespace super_hse {

Level::Level(std::string filename) {
    ldtk_filename = filename;
    try {
        project.loadFromFile(ldtk_filename);
        std::cout << "LDtk World \"" << project.getFilePath()
                  << "\" was loaded successfully." << std::endl;
        init();
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void Level::init() {
    auto &world = project.allWorlds().at(0);
    auto &ldtk_first_level =
        world.getLevel("Level_1");  // передали проект и забрали оттуда уровень
    TileMap::path = project.getFilePath().directory(
    );  // достали папку где лежит проект, чтобы потом там искать текстуры
    tilemap.load(ldtk_first_level);  // загружаем стои конкретного уровня
}

void Level::render(sf::RenderTarget &target) {
    target.draw(tilemap.getLayer("Background")
    );  // заюираем слой и отдаем на отрисовку
    target.draw(tilemap.getLayer("Ground"));
    target.draw(tilemap.getLayer("Clouds"));
    target.draw(tilemap.getLayer("Grass"));
    target.draw(tilemap.getLayer("Texture_bricks"));
}
}  // namespace super_hse

#endif
