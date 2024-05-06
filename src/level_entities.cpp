#ifndef LEVEL_ENTITIES_CPP
#define LEVEL_ENTITIES_CPP

#include "level_entities.hpp"

namespace super_hse{
void level_entities::draw(sf::RenderTarget &target){
    for (auto &elem : coins){
        if (elem.get_status() != CoinStatus::dead){
            target.draw(elem.coin_sprite);
        }
    }
    for (auto &elem : enemies){
        if (elem.get_state() != EnemyState::dead){
            target.draw(elem.enemySprite);
        }
    }
}

void level_entities::check_coin_collision(sf::FloatRect &nextPositionCollider){
    for (auto &coin : coins){
        if (nextPositionCollider.intersects(coin.coin_sprite.getGlobalBounds())){
            coin.disable();
        }
    }
}

void level_entities::check_enemy_collision(sf::FloatRect &nextPositionCollider, Player &player, sf::Vector2f &movement){
    for (auto &enemy : enemies){
        if (nextPositionCollider.intersects(enemy.enemySprite.getGlobalBounds()) && enemy.get_state() == EnemyState::active){
            if (nextPositionCollider.top + nextPositionCollider.height - 4 <= enemy.enemySprite.getPosition().y && movement.y > 0){
                enemy.disable();
            }else{
                if (enemy.get_state() == EnemyState::active){
                    player.lose_life();
                }
                enemy.unable();
            }
        }
    }
}

}

#endif
