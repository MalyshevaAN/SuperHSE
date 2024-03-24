#ifndef COIN_HPP_
#define COIN_HPP_

#include <SFML/Graphics.hpp>

namespace super_hse{
    struct coin{
        sf::Sprite coin_sprite;
        static const int coinHeight = 16;
        static const int coinWidth = 16;
        void disable();
        bool get_status();
        void spin_and_dissappear();

    private:
        bool is_active = true;

    };
}


#endif
