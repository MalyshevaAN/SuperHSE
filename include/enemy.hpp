#ifndef ENEMY_HPP_
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "hse_utils.hpp"
namespace super_hse {

    struct enemy{
        sf::Sprite enemySprite;
        sf::Texture enemyTexture;
        float posX;
        float posY;

        enemy(float x_, float y_);
        bool get_status();
        void change_status();
        void die();
    private:
        bool is_alive = true;
    };
}

#endif
