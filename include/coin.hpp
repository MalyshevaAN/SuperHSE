#ifndef COIN_HPP_
#define COIN_HPP_

#include <SFML/Graphics.hpp>

namespace super_hse {
struct coin {
    sf::Sprite coin_sprite;
    void disable();
    bool get_status();

private:
    bool is_active = true;
};
}  // namespace super_hse

#endif
