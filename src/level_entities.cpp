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
        try {
            auto &coinLayer = ldtk_first_level.getLayer("HSEcoin");
            for (ldtk::Entity &entity : coinLayer.getEntitiesByName("Coin")) {
                coin new_coin;
                new_coin.setStatus(CoinStatus::active);
                new_coin.coin_sprite.setTextureRect(sf::IntRect(0,0,coin::coinWidth,coin::coinHeight));
                new_coin.coin_sprite.setPosition(sf::Vector2f(entity.getPosition().x, entity.getPosition().y));
                coins.emplace_back(new_coin);
            }
        }catch(...){
            throw noSuchLayer("HSEcoin");
        }
        try{
            auto &enemyLayer = ldtk_first_level.getLayer("Enemies");
            for (ldtk::Entity &entity : enemyLayer.getEntitiesByName("Enemy")) {
                enemy new_enemy(entity.getPosition().x, entity.getPosition().y);
                new_enemy.enemySprite.setTextureRect(sf::IntRect(0, 0, 64, 16));
                new_enemy.enemySprite.setPosition(sf::Vector2f(entity.getPosition().x, entity.getPosition().y));
                enemies.emplace_back(new_enemy);
            }
        }catch(...){
            throw noSuchLayer("Enemies");
        }
    }catch(...){
        throw noSuchLevel("Level_1");
    }
};

void level_entities::check_coin_collision(sf::FloatRect &nextPositionCollider, answer &answer_){
    for (int i = 0; i < coins.size(); ++i){
        if (nextPositionCollider.intersects(coins[i].coin_sprite.getGlobalBounds())){
            coins[i].disable();
            answer_.gathered_coin_index = i;
        }
    }
}

void level_entities::check_enemy_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement, answer &answer_){
    for (int i = 0; i < enemies.size(); ++i){
        if (nextPositionCollider.intersects(enemies[i].enemySprite.getGlobalBounds()) && enemies[i].get_state() == EnemyState::active){
            if (nextPositionCollider.top + nextPositionCollider.height - 4 <= enemies[i].enemySprite.getPosition().y && movement.y > 0){
                enemies[i].disable();
                answer_.killed_enemy_index = i;
            }else{
                if (enemies[i].get_state() == EnemyState::active){
                    enemies[i].unable();
                    answer_.run_into_enemy_index = i;
                    answer_.lose_life = true;
                }
                enemies[i].unable();
            }
        }
    }
}

void level_entities::check_collider_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement, answer &answer_){
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
                    nextPositionCollider.left -= movement.x;
                    movement.x = 0;
                }
            } else {
                isCollidingWithWall = true;
            }
        }
    }
    answer_.movement_x = movement.x;
    answer_.movement_y = movement.y;
    answer_.isCollidingWithWall = isCollidingWithWall;
    answer_.isCollidingWithFloor = isCollidingWithFloor;
}

answer level_entities::update(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement){
    answer answer_;
    check_collider_collision(nextPositionCollider, movement, answer_);
    check_coin_collision(nextPositionCollider, answer_);
    check_enemy_collision(nextPositionCollider, movement, answer_);
    return answer_;
}

}

#endif
