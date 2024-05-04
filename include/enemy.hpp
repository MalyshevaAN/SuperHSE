#ifndef ENEMY_HPP_
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "hse_utils.hpp"
#include "entity.hpp"

namespace super_hse {

    struct enemy : entity{
        static inline sf::Texture enemyTexture;
        static inline sf::Texture enemyUnactiveTexture;
        float posX;
        float posY;
        enemy();
        enemy(float x_, float y_);
        void disable() override;
        void change(int frame) override;
        void change_pos();
        void unable() override;
        void disappear() override;
        static void init();
        static inline sf::SoundBuffer buffer;
        static inline sf::Sound sound;
    private:
        float time_unable = 0;
        float time_dissappearing = 0;
        float pos_diff;
        int path = 1;
    };
}

#endif
