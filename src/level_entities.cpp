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

int level_entities::check_coin_collision(sf::FloatRect &nextPositionCollider){
    for (int i = 0; i < coins.size(); ++i){
        if (nextPositionCollider.intersects(coins[i].coin_sprite.getGlobalBounds())){
            coins[i].disable();
            return i;
        }
    }
    return -1;
}

std::pair<bool, int> level_entities::check_enemy_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement){
    for (int i = 0; i < enemies.size(); ++i){
        if (nextPositionCollider.intersects(enemies[i].enemySprite.getGlobalBounds()) && enemies[i].get_state() == EnemyState::active){
            if (nextPositionCollider.top + nextPositionCollider.height - 4 <= enemies[i].enemySprite.getPosition().y && movement.y > 0){
                enemies[i].disable();
                return {false, i};
            }else{
                if (enemies[i].get_state() == EnemyState::active){
                    enemies[i].unable();
                    return {true, i};
                }
                enemies[i].unable();
            }
        }
    }
    return {false, -1};
}

std::pair<bool, bool> level_entities::check_collider_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement){
    bool isCollidingWithWall = false;
    bool isCollidingWithFloor = false;
    // std::cerr << movement.x << ' ' << movement.y << '\n';
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
                nextPositionCollider.top -= 1;
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

answer level_entities::update(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement){
    answer answer_;
    std::pair<bool, bool> collide_with_block = check_collider_collision(nextPositionCollider, movement);
    answer_.isCollidingWithWall = collide_with_block.first;
    answer_.isCollidingWithFloor = collide_with_block.second;
    answer_.gathered_coin_index = check_coin_collision(nextPositionCollider);
    std::pair<bool,int> collide_with_enemy = check_enemy_collision(nextPositionCollider, movement);
    if(collide_with_enemy.first == true){
        answer_.lose_life = true;
        answer_.run_into_enemy_index = collide_with_enemy.second;
    }else {
        answer_.killed_enemy_index = collide_with_enemy.second;
    }
    return answer_;
}

}

#endif
