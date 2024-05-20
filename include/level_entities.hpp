#ifndef LEVEL_ENTITIES_HPP
#define LEVEL_ENTITIES_HPP

#include "coin.hpp"
#include "enemy.hpp"
#include "brick.hpp"
#include <SFML/Graphics.hpp>
#include <LDtkLoader/Project.hpp>
#include "level_info.hpp"
#include "messages.hpp"
#include <vector>

namespace super_hse{
struct level_entities{
    std::vector<brick> colliders;
    std::vector<coin> coins;
    std::vector<enemy> enemies;
    ldtk::Project project;
    LevelInfo info;


    void init(std::string description_file);

    void check_collider_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement, answer &answer_);

    void check_coin_collision(sf::FloatRect &nextPositionCollider, answer &answer_);

    void check_enemy_collision(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement, answer &answer_);

    answer update(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement);
};
}


#endif
