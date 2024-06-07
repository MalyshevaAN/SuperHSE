#ifndef LEVEL_ENTITIES_HPP
#define LEVEL_ENTITIES_HPP

#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "brick.hpp"
#include "coin.hpp"
#include "enemy.hpp"
#include "level_info.hpp"
#include "messages.hpp"

namespace super_hse {
struct level_entities {
    std::vector<brick> colliders;
    std::vector<coin> coins;
    std::vector<enemy> enemies;
    ldtk::Project project;
    LevelInfo info;

    void init(std::string description_file);

    void check_collider_collision(
        sf::FloatRect &nextPositionCollider,
        sf::Vector2f &movement,
        answer &answer_
    );

    void
    check_coin_collision(sf::FloatRect &nextPositionCollider, answer &answer_);

    void check_enemy_collision(
        sf::FloatRect &nextPositionCollider,
        sf::Vector2f &movement,
        answer &answer_
    );

    answer update(sf::FloatRect &nextPositionCollider, sf::Vector2f &movement);
};
}  // namespace super_hse

#endif
