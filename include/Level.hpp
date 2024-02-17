#ifndef LEVEL_HPP_
#define LEVEL_HPP_
#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

namespace super_hse {
struct Level {
    TileMap tilemap;  // сама карта тайлов для этого уровня

    void init(const ldtk::Project &project);

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
