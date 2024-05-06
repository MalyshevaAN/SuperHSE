#ifndef LEVEL_HPP_
#define LEVEL_HPP_
#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "TileMap.hpp"
#include "coin.hpp"
#include "enemy.hpp"
#include "brick.hpp"
#include "player.hpp"
#include "level_entities.hpp"

namespace super_hse {

struct Level {
    Level() = default;
    Level(std::string filename);
    std::string
        ldtk_filename;  // файл на основе которого всё строем теперь как поле
    TileMap tilemap;  // сама карта тайлов для этого уровня
    ldtk::Project project;  // сделала проект откуда берем уровень его полем
    int level_number;
    level_entities entities;
    std::vector<std::string> textureColliders;
    sf::View view;
    sf::Texture coinTexture;
    sf::Texture brickTexture;
    sf::Texture floorTexture;
    sf::Texture enemyTexture;
    sf::Texture lifeTexture;
    sf::Texture deathTexure;
    sf::RectangleShape coinCounterBack{};
    sf::RectangleShape coinCounterFront{};
    int level_lives = 3;
    std::vector<sf::Sprite> lives;
    void get_textures();
    int allCoins = 0;
    const float frameSpeed = 0.004;
    float currentFrameColumn = 0;
    std::map<std::string, sf::Texture> textures = {
        {"coin", coinTexture},
        {"brick", brickTexture},
        {"floor", floorTexture},
        {"enemy", enemyTexture},
        {"life", lifeTexture}, 
        {"death", deathTexure}};
    void init(
        std::vector<std::string> &tileLayerName,
        std::vector<std::string> &entityLayerNames,
        std::vector<std::string> &colliderNames,
        int level_number_
    );

    void init_enemies();
    void
    render(sf::RenderTarget &target, std::vector<std::string> &tileLayerName);
    void update(sf::Time &dTime, Position player_pos, int player_lives);
};

}  // namespace super_hse

#endif

// что вообще есть:
// есть проект - это весь ldtk файл, в нём вообще всё, он парсится как json
// в проекте есть миры, у нас вроде один это не так важно
// в мире есть уровни - разберусь как делать в одном мире несколько уровней,
// будет топово в каждом уровне миллион слоёв, которые накладываются друг на
// друга конкретно сейчас подгружаются только тайловые слои по сути нам
// понадобятся они и еще слои entity, чтобы они как колладеры были, научусь
// подгружать их тоже

// ** следующие шаги - выгрузка объектов столкновения именно как коллайдеров,
// плюс создание enum-ов и мап, для передачи разных уровней
