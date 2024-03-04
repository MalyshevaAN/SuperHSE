#ifndef LEVEL_CPP_
#define LEVEL_CPP_

#include "Level.hpp"
#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include "TileMap.hpp"
#include <filesystem>

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
                sf::FloatRect rect(
                    (float)entity.getPosition().x,
                    (float)entity.getPosition().y, (float)entity.getSize().x,
                    (float)entity.getSize().y
                );
                colliders.emplace_back(rect);
                if (name!="Floor"){
                    colorColliders.emplace_back(sf::Color::Red);
                }else {
                    colorColliders.emplace_back(sf::Color(0, 0, 0, 0));
                }
            }
        }
    }
    auto &coinLayer = ldtk_first_level.getLayer("HSEcoin");
    sf::Texture coinTexture;
    std::filesystem::path p = std::filesystem::current_path();
    if (!coinTexture.loadFromFile(p.parent_path().string() + "/assets/images/coin.png")){
        std::cerr << "Error loading coin";
    }
    for (ldtk::Entity &entity : coinLayer.getEntitiesByName("Coin")){
        sf::Sprite coin;
        coin.setPosition(sf::Vector2f(entity.getPosition().x, entity.getPosition().y));
        coin.setTexture(coinTexture);
        coin.setTextureRect(sf::IntRect(0,0,16,16));
        coins.emplace_back(coin);
    }
}

sf::RectangleShape Level::getColliderShape(const sf::FloatRect &rect, sf::Color color) {
    sf::RectangleShape r({rect.width, rect.height});
    sf::Texture texture;
    r.setPosition(rect.left, rect.top);
    r.setFillColor(color);  // поменять на красивую текстуру!!!
    //std::filesystem::path p(std::filesystem::current_path());
    //texture.loadFromFile(p.parent_path().string() + "/assets/tilemaps/materials/brick.jpg");
    return r;
}

void Level::render(
    sf::RenderTarget &target,
    std::vector<std::string> &tileLayerName
) {
    for (auto elem : tileLayerName) {
        target.draw(tilemap.getLayer(elem));
    }
    for (size_t i = 0; i < colliders.size(); i++){
        target.draw(getColliderShape(colliders[i], colorColliders[i]));
    }
    for (auto elem : coins){
        target.draw(elem);
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
    std::filesystem::path p(std::filesystem::current_path());
    auto level1 = std::make_unique<LevelInfo>(p.parent_path().string() + "/assets/files/level2.txt");
    storage.push_back(std::move(level1));
}  
}  // namespace super_hse
#endif
