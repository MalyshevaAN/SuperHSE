#ifndef COIN_HPP_
#define COIN_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "entity.hpp"

namespace super_hse{
    struct coin : public entity{
        static const int coinHeight = 16;
        static const int coinWidth = 16;
        void disable() override;
        EntityStatus get_status();
        void disappear() override;
        void change(int frame) override;
        void unable() override;
        static void init();
        static inline sf::SoundBuffer buffer;
        static inline sf::Sound sound;

        static inline EntityType type;

    private:
        float height_change = 0;
    };
}


#endif
