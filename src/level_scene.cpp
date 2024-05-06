#include "level_scene.hpp"
#include <LDtkLoader/Project.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "Level.hpp"
#include "TileMap.hpp"
#include "level_map_scene.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"
#include "game.hpp"
#include "lose_scene.hpp"

namespace super_hse {

LevelScene::LevelScene(int levelN) {
    levelNumber = levelN;
    std::string filename = storage.storage.at(levelNumber)->filename;
    level.ldtk_filename = filename;
    level.project.loadFromFile(filename);
    level.init(
        storage.storage.at(levelNumber)->tileLayerName,
        storage.storage.at(levelNumber)->entityLayerName,
        storage.storage.at(levelNumber)->colliderName,
        levelN
    );
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
    // player.handleInput(event);
}

void LevelScene::updateSceneSize() {
}

void LevelScene::update(sf::Time &dTime) {
    if (player.get_active_lives() == 0){
        SceneManager::changeScene(std::make_unique<LoseScene>());
        std::cerr << 1;
        return;
    }
    level.update(dTime, player.get_position(), player.get_active_lives());
    player.update(dTime);
    // посчитаем следующую возможную позицию игрока
    sf::FloatRect nextPositionCollider = player.getCollider();
    sf::Vector2f movement = player.calcMovement(dTime);
    nextPositionCollider.left += movement.x;
    nextPositionCollider.top += movement.y;

    // Проверяем, будет ли пересечение с блоками
    const float dTimeSeconds = dTime.asSeconds();

    // bool isCollidingWithWall = false;
    // bool isCollidingWithFloor = false;
    // for (auto &entity : level.entities.colliders) {
    //     sf::FloatRect intersect;
    //     if (nextPositionCollider.intersects(entity.brickRect, intersect)) {
    //         // проверить тип объекта, с кем пересеклись (в данном случае -
    //         // стены/пол)
    //         // TODO - добавить проверку на тип объекта (тут нужна Настя и её
    //         // енамы)

    //         // проверка что пересекаемся с полом
    //         if (nextPositionCollider.top + nextPositionCollider.height >=
    //             entity.brickRect.top) {
    //             isCollidingWithFloor = true;
    //             nextPositionCollider.top -= movement.y;
    //             movement.y = 0;

    //             // если после отката человечка наверх мы всё равно пересекаемся
    //             // с блоком - значит он стена
    //             if (nextPositionCollider.intersects(entity.brickRect, intersect)) {
    //                 isCollidingWithWall = true;
    //             }
    //         } else {
    //             isCollidingWithWall = true;
    //         }
    //     }
    // }
    std::pair<bool, bool> collision = level.entities.check_collider_collision(nextPositionCollider, movement);
    bool isCollidingWithWall = collision.first;
    bool isCollidingWithFloor = collision.second;
    level.entities.check_coin_collision(nextPositionCollider);
    if(level.entities.check_enemy_collision(nextPositionCollider, movement)){
        player.lose_life();
    }

    player.isGrounded = isCollidingWithFloor;

    if (!isCollidingWithWall) {
        player.move(movement.x, 0);
    }
    if (!isCollidingWithFloor) {
        player.move(0, movement.y);
    }

    // обновление фрейма
}

void LevelScene::draw(sf::RenderWindow &window) {
    window.clear(windowFillColor);
    level.render(window, storage.storage.at(levelNumber)->tileLayerName);
    player.draw(window);
    window.display();
}
} // namespace super_hse
