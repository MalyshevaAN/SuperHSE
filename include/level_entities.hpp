#ifndef LEVEL_ENTITIES_HPP
#define LEVEL_ENTITIES_HPP

#include "coin.hpp"
#include "enemy.hpp"
#include "brick.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace super_hse{
struct level_entities{
    std::vector<brick> colliders;
    std::vector<coin> coins;
    std::vector<enemy> enemies;

    void draw(sf::RenderTarget &target);

    std::pair<bool, bool> check_collider_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement);

    void check_coin_collision(sf::FloatRect &nextPositionCollider);

    void check_enemy_collision(sf::FloatRect &nextPositionCollider, Player &player, sf::Vector2f &movement);
};
}


#endif
