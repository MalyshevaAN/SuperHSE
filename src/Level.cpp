#ifndef LEVEL_CPP_
#define LEVEL_CPP_

#include "Level.hpp"
#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
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
    sf::Texture texture;
    r.setPosition(rect.left, rect.top);
    texture.loadFromFile("../assets/tilemaps/materials/orangebrick.png");
    //r.setFillColor(sf::Color(100, 100, 200));  // поменять на красивую текстуру!!!
    r.setTexture(&texture);
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

LevelInfo::LevelInfo(std::string file) {
    std::string line;
    std::ifstream in(file);
    if (in.is_open()) {
        std::getline(in, line);
        filename = line.substr(0, line.size());
        std::getline(in, line);
        std::getline(in, line);
        while (!line.empty()) {
            tileLayerName.push_back(line);
            std::getline(in, line);
        }
        std::getline(in, line);
        while (!line.empty()) {
            entityLayerName.push_back(line);
            std::getline(in, line);
        }
        std::getline(in, line);
        while (!line.empty()) {
            colliderName.push_back(line);
            std::getline(in, line);
        }
    } else {
        throw 1;
    }
}

LevelsStorage::LevelsStorage() {
    auto level1 = std::make_unique<LevelInfo>("../assets/files/level2.txt");
    storage.push_back(std::move(level1));
}  // namespace super_hse
}  // namespace super_hse
#endif
