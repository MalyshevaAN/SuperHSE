#ifndef LEVEL_ENTITIES_CPP
#define LEVEL_ENTITIES_CPP

#include "level_entities.hpp"
#include "hse_utils.hpp"
#include <LDtkLoader/Project.hpp>

namespace super_hse{


void level_entities::init(std::string description_file){
    info = LevelInfo(description_file);
    brick::init();
    project.loadFromFile(info.filename);
    auto &world = project.allWorlds().at(0);
    try{
        auto &ldtk_first_level =
            world.getLevel("Level_1");  // передали проект и забрали оттуда уровень  // достали папку где лежит проект, чтобы потом там искать текстуры
        for (auto elem : info.entityLayerName) {
            auto &entitiesLayer = ldtk_first_level.getLayer(elem);
            for (auto name : info.colliderName) {
                for (ldtk::Entity &entity : entitiesLayer.getEntitiesByName(name)) {
                    std::string texture_name = "brick";
                    if (name == "Floor" || name == "FloorSmall" || name == "FloorMedium"){
                        texture_name = "floor";
                    }
                    brick new_brick(entity.getPosition().x, entity.getPosition().y, entity.getSize().x, entity.getSize().y, texture_name);
                    colliders.emplace_back(new_brick);
                }
            }
        }
    }catch(...){
        throw noSuchLevel("Level_1");
    }
};

void level_entities::check_coin_collision(sf::FloatRect &nextPositionCollider){
    for (auto &coin : coins){
        if (nextPositionCollider.intersects(coin.coin_sprite.getGlobalBounds())){
            coin.disable();
        }
    }
}

bool level_entities::check_enemy_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement){
    for (auto &enemy : enemies){
        if (nextPositionCollider.intersects(enemy.enemySprite.getGlobalBounds()) && enemy.get_state() == EnemyState::active){
            if (nextPositionCollider.top + nextPositionCollider.height - 4 <= enemy.enemySprite.getPosition().y && movement.y > 0){
                enemy.disable();
            }else{
                if (enemy.get_state() == EnemyState::active){
                    enemy.unable();
                    return true;
                }
                enemy.unable();
            }
        }
    }
    return false;
}

std::pair<bool, bool> level_entities::check_collider_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement){
    bool isCollidingWithWall = false;
    bool isCollidingWithFloor = false;
    for (auto &entity : colliders) {
        sf::FloatRect intersect;
        if (nextPositionCollider.intersects(entity.brickRect, intersect)) {
            // проверить тип объекта, с кем пересеклись (в данном случае -
            // стены/пол)
            // TODO - добавить проверку на тип объекта (тут нужна Настя и её
            // енамы)

            // проверка что пересекаемся с полом
            if (nextPositionCollider.top + nextPositionCollider.height >=
                entity.brickRect.top) {
                isCollidingWithFloor = true;
                nextPositionCollider.top -= movement.y;
                movement.y = 0;

                // если после отката человечка наверх мы всё равно пересекаемся
                // с блоком - значит он стена
                if (nextPositionCollider.intersects(entity.brickRect, intersect)) {
                    isCollidingWithWall = true;
                }
            } else {
                isCollidingWithWall = true;
            }
        }
    }

    return {isCollidingWithWall, isCollidingWithFloor};
}

}

#endif
