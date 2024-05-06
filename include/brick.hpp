#ifndef BRICK_HPP
#define BRICK_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace super_hse{
struct brick{
    sf::Sprite brick_sprite;
    sf::FloatRect brickRect;

    static inline sf::Texture brickTexture;
    static inline sf::Texture floorTexture;

    static void init();
    brick(int left, int top, int width, int height, const std::string textureName);
};
}

#endif
