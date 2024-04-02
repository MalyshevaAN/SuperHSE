#ifndef COIN_HPP_
#define COIN_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace super_hse{
    enum class CoinStatus {
        active,
        dieing,
        dead
    };

    struct coin{
        sf::Sprite coin_sprite;
        static const int coinHeight = 16;
        static const int coinWidth = 16;
        void disable();
        CoinStatus get_status();
        void disappear();
        void changeFrame(int frame);
        void setStatus(CoinStatus status_);
        static void init();
        static inline sf::SoundBuffer buffer;
        static inline sf::Sound sound;

    private:
        CoinStatus status = CoinStatus::active;
        float height_change = 0;
    };
}


#endif
