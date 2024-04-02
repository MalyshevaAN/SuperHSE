#ifndef ENEMY_HPP_
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "hse_utils.hpp"
namespace super_hse {

    enum class EnemyState{
        active,
        not_active,
        dieing,
        dead
    };

    struct enemy{
        sf::Sprite enemySprite;
        sf::Texture enemyTexture;
        float posX;
        float posY;

        enemy(float x_, float y_);
        EnemyState get_state();
        void disable();
        void unable();
        void disappear();
        static void init();
        static inline sf::SoundBuffer buffer;
        static inline sf::Sound sound;
    private:
        EnemyState state = EnemyState::active;
        float time_unable = 0;
        float time_dissappearing = 0;
    };
}

#endif
