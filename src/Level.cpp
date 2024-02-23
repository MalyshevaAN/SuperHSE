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
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void Level::init(
    std::vector<std::string> &tileLayerName,
    std::vector<std::string> &entityLayerNames,
    std::vector<std::string> &colliderNames
) {
    auto &world = project.allWorlds().at(0);
    auto &ldtk_first_level =
        world.getLevel("Level_1");  // передали проект и забрали оттуда уровень
    TileMap::path = project.getFilePath().directory(
    );  // достали папку где лежит проект, чтобы потом там искать текстуры
    tilemap.load(ldtk_first_level);  // загружаем слои конкретного уровня
    for (auto elem : entityLayerNames) {
        auto &entitiesLayer = ldtk_first_level.getLayer(elem);
        for (auto name : colliderNames) {
            for (ldtk::Entity &entity : entitiesLayer.getEntitiesByName(name)) {
                colliders.emplace_back(
                    (float)entity.getPosition().x,
                    (float)entity.getPosition().y, (float)entity.getSize().x,
                    (float)entity.getSize().y
                );
            }
        }
    }
}

sf::RectangleShape Level::getColliderShape(const sf::FloatRect &rect) {
    sf::RectangleShape r({rect.width, rect.height});
    r.setPosition(rect.left, rect.top);
    r.setFillColor(sf::Color::Red);  // поменять на красивую текстуру!!!
    return r;
}

void Level::render(
    sf::RenderTarget &target,
    std::vector<std::string> &tileLayerName
) {
    for (auto elem : tileLayerName) {
        target.draw(tilemap.getLayer(elem));
    }
    for (auto &entity : colliders) {
        target.draw(getColliderShape(entity));
    }
}
}  // namespace super_hse

LevelsStorage::LevelsStorage() {
    auto level1 = std::make_unique<LevelInfo>();
    level1->filename = "../assets/tilemaps/first_level2.ldtk";
    level1->colliderName.push_back("OrangeBrick");
    level1->colliderName.push_back("WhiteBrick");
    level1->entityLayerName.push_back("Bricks");
    level1->tileLayerName.push_back("Background");
    level1->tileLayerName.push_back("Ground");
    level1->tileLayerName.push_back("Clouds");
    level1->tileLayerName.push_back("Grass");
    level1->tileLayerName.push_back("Texture_bricks");
    storage.push_back(std::move(level1));
}  // namespace super_hse

#endif
