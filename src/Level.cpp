#ifndef LEVEL_CPP_
#define LEVEL_CPP_

#include "Level.hpp"
#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "TileMap.hpp"
#include "coin.hpp"
#include "hse_utils.hpp"
#include "coin.hpp"
#include "game.hpp"
#include "player.hpp"
#include "lose_scene.hpp"
#include "win_scene.hpp"

namespace super_hse {

Level::Level(std::string filename) {
    ldtk_filename = filename;
    try {
        project.loadFromFile(ldtk_filename);
        std::cout << "LDtk World \"" << project.getFilePath()
                  << "\" was loaded successfully." << std::endl;
    } catch (std::exception &ex) {
        throw noSuchLdtkProject(ldtk_filename);
    }
    view.setSize(Game::windowWidth, Game::windowHeight);
    view.setCenter(Game::windowWidth / 2, Game::windowHeight / 3);
}

void Level::get_textures(){
    get_texture_from_file("HSEcoin.png", coinTexture);
    get_texture_from_file("bricks.png", textures.at("brick"));
    get_texture_from_file("floor.png", textures.at("floor"));
    get_texture_from_file("enemy.png", textures.at("enemy"));
    get_texture_from_file("life.png", textures.at("life"));
    get_texture_from_file("death.png", textures.at("death"));
}

void Level::init(
    std::vector<std::string> &tileLayerName,
    std::vector<std::string> &entityLayerNames,
    std::vector<std::string> &colliderNames,
    int level_number_
) {
    get_textures();
    coin::init();
    enemy::init();
    level_number = level_number_;
    auto &world = project.allWorlds().at(0);
    try{
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
                    if (name != "Floor" && name != "FloorSmall" && name != "FloorMedium") {
                        textureColliders.emplace_back("brick");
                    } else {
                        textureColliders.emplace_back("floor");
                    }
                }
            }
        }
        try {
            auto &coinLayer = ldtk_first_level.getLayer("HSEcoin");
            for (ldtk::Entity &entity : coinLayer.getEntitiesByName("Coin")) {
                coin new_coin;
                new_coin.setStatus(CoinStatus::active);
                new_coin.coin_sprite.setTexture(coinTexture);
                new_coin.coin_sprite.setTextureRect(sf::IntRect(0,0,coin::coinWidth,coin::coinHeight));
                new_coin.coin_sprite.setPosition(sf::Vector2f(entity.getPosition().x, entity.getPosition().y));
                coins.emplace_back(new_coin);
            }
            allCoins = coins.size();
        }catch(...){
            throw noSuchLayer("HSEcoin");
        }
        try{
            auto &enemyLayer = ldtk_first_level.getLayer("Enemies");
            for (ldtk::Entity &entity : enemyLayer.getEntitiesByName("Enemy")) {
                enemy new_enemy(entity.getPosition().x, entity.getPosition().y);
                new_enemy.enemySprite.setTexture(textures.at("enemy"));
                new_enemy.enemySprite.setPosition(sf::Vector2f(entity.getPosition().x, entity.getPosition().y));
                enemies.push_back(new_enemy);
            }
        }catch(...){
            throw noSuchLayer("Enemies");
        }
    }catch(...){
        throw noSuchLevel("Level_1");
    }

    coinCounterBack.setSize({(float)Game::windowWidth / 10, (float)Game::windowHeight / 20});
    coinCounterBack.setPosition({(float)(Game::windowWidth / 1.3), (float)Game::windowHeight / 40});
    coinCounterBack.setFillColor(sf::Color::White);
    coinCounterFront.setPosition(coinCounterBack.getPosition());
    coinCounterFront.setFillColor(sf::Color::Green);
    coinCounterFront.setSize({0, coinCounterBack.getSize().y});
    for (int i = 0; i < 3; ++i){
        sf::Sprite new_life;
        new_life.setTexture(textures.at("life"));
        new_life.setPosition(Game::windowWidth / 1.1 + i * 35, Game::windowHeight / 40);
        lives.push_back(new_life);
    }
}

sf::RectangleShape
Level::getColliderShape(const sf::FloatRect &rect, std::string texture_name) {
    sf::RectangleShape r({rect.width, rect.height});
    r.setPosition(rect.left, rect.top);
    r.setTexture(&textures.at(texture_name));
    r.setTextureRect(sf::IntRect(0, 0, rect.width, rect.height));
    return r;
}

void Level::update(sf::Time &dTime, Position player_pos, int player_lives) {
    if (player_lives == 0){
        view.setCenter(Game::windowWidth / 2, Game::windowHeight / 3);
        return;
    }

    if (player_pos.x >= tilemap.width - 60){
        int gatheredCoins = 0;
        for (auto &elem : coins) {
            if (elem.get_status() != CoinStatus::active){
                gatheredCoins++;
            }
        };

        SceneManager::changeScene(std::make_unique<WinScene>(gatheredCoins, level_number + 1, player_lives));
        return;
    }
    int diff = Game::windowWidth / 2 - Player::start_position_x;
    if (player_pos.x + diff >= Game::windowWidth / 2  && player_pos.x + diff < tilemap.width - 580){
        view.setSize(Game::windowWidth, Game::windowHeight);
        view.setCenter(player_pos.x + diff, Game::windowHeight / 3);
        coinCounterBack.setPosition(player_pos.x - Player::start_position_x + Game::windowWidth / 1.3, coinCounterBack.getPosition().y);
        coinCounterFront.setPosition(coinCounterBack.getPosition());
        for (int i = 0; i < 3; ++i){
            lives[i].setPosition(player_pos.x - Player::start_position_x + Game::windowWidth / 1.1 + i*35, lives[i].getPosition().y);
            if (i < player_lives){
                lives[i].setTexture(textures.at("life"));
            }else{
                lives[i].setTexture(textures.at("death"));
            }
        }
    }
    currentFrameColumn += frameSpeed * dTime.asMilliseconds();
    if (currentFrameColumn >= 5) {
        currentFrameColumn -= 5;
    }
    int gatheredCoins = 0;
    for (auto &elem : coins) {
        if (elem.get_status() == CoinStatus::active){
            elem.changeFrame(currentFrameColumn);
        }else {
            if (elem.get_status() == CoinStatus::dieing){
                elem.changeFrame(currentFrameColumn);
                elem.disappear();
            }
            gatheredCoins++;
        };
    }
    for (auto &enemy : enemies){
        if (enemy.get_state() == EnemyState::dieing){
            enemy.disappear();
        }
        if (enemy.get_state() == EnemyState::not_active){
            enemy.unable();
        }
        if (enemy.get_state() == EnemyState::active || enemy.get_state() == EnemyState::not_active){
            enemy.change_pos();
        }
    }
    coinCounterFront.setSize({(coinCounterBack.getSize().x / allCoins) * gatheredCoins, coinCounterBack.getSize().y});
}

void Level::render(
    sf::RenderTarget &target,
    std::vector<std::string> &tileLayerName
) {
    target.setView(view);
    for (auto &elem : tileLayerName) {
        target.draw(tilemap.getLayer(elem));
    }
    for (size_t i = 0; i < colliders.size(); i++) {
        target.draw(getColliderShape(colliders[i], textureColliders[i]));
    }
    for (auto &elem : coins) {
        if (elem.get_status() != CoinStatus::dead){
            target.draw(elem.coin_sprite);
        }
    }
    for (auto &elem : enemies){
        if (elem.get_state() != EnemyState::dead){
            target.draw(elem.enemySprite);
        }
    }
    for (auto &life : lives){
        target.draw(life);

    }
    target.draw(coinCounterBack);
    target.draw(coinCounterFront);
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
        throw noSuchDescriptionFile(file);
    }
}

LevelsStorage::LevelsStorage() {
    std::filesystem::path p(std::filesystem::current_path());
    auto level1 = std::make_unique<LevelInfo>(
        p.parent_path().string() + "/assets/files/level2.txt"
    );

    auto level2 = std::make_unique<LevelInfo>(
        p.parent_path().string() + "/assets/files/level3.txt"
    );
    storage.push_back(std::move(level1));
    storage.push_back(std::move(level2));
}
}  // namespace super_hse
#endif
