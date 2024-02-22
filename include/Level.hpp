#ifndef LEVEL_HPP_
#define LEVEL_HPP_
#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

namespace super_hse {
struct Level {
    Level() = default;
    Level(std::string filename);
    std::string
        ldtk_filename;  // файл на основе которого всё строем теперь как поле
    TileMap tilemap;  // сама карта тайлов для этого уровня

    ldtk::Project project;  // сделала проект откуда берем уровень его полем
    void init();

    void render(sf::RenderTarget &target);
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
