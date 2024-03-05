#ifndef LEVEL_HPP_
#define LEVEL_HPP_
#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileMap.hpp"
#include <map>

namespace super_hse {

struct Level {

    Level() = default;
    Level(std::string filename);
    std::string
        ldtk_filename;  // файл на основе которого всё строем теперь как поле
    TileMap tilemap;  // сама карта тайлов для этого уровня
    ldtk::Project project;  // сделала проект откуда берем уровень его полем

    std::vector<sf::FloatRect> colliders;
    std::vector<sf::Sprite> coins;
    std::vector<std::string> textureColliders;
    sf::Texture coinTexture;
    sf::Texture brickTexture;
    sf::Texture floorTexture;
    const int coinHeight = 16;
    const int coinWidth = 16;
    const float frameSpeed = 0.004;
    float currentFrameColumn = 0;
    std::map<std::string, sf::Texture> textures = {
        {"coin", coinTexture},
        {"brick", brickTexture},
        {"floor", floorTexture}
    };
    void init(
        std::vector<std::string> &tileLayerName,
        std::vector<std::string> &entityLayerNames,
        std::vector<std::string> &colliderNames
    );

    sf::RectangleShape getColliderShape(const sf::FloatRect &rect, std::string texture_name);

    void
    render(sf::RenderTarget &target, std::vector<std::string> &tileLayerName);
    void update(sf::Time &dTime);
};

struct LevelInfo;

struct LevelsStorage {
    std::vector<std::unique_ptr<LevelInfo>> storage;

    LevelsStorage();
};

struct LevelInfo {
    std::string filename;
    std::vector<std::string> tileLayerName;
    std::vector<std::string> entityLayerName;
    std::vector<std::string> colliderName;

    LevelInfo() = default;

    LevelInfo(std::string file);

    friend LevelsStorage;
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
