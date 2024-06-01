#ifndef PLAYER_ICON_HPP
#define PLAYER_ICON_HPP

#include <SFML/Graphics.hpp>
#include "player.hpp"

namespace super_hse{

// struct Position{
//     float x;
//     float y;
// };

class Player_icon {
private:
    sf::Texture playerIconPicture;
    sf::Sprite sprite;
    Position position = {0,0};
    bool get_texture = false;
    int currentFrameColumn = 0;
    int currentFrameRow = 11;
    int totalFrames = 6;
    const int frameWidth = 64;
    const int frameHeight = 64;
    const float frameSpeed = 0.008;

public:

    Player_icon();
    void update(float x, float y, int skin_id, int row, int col);
    void draw(sf::RenderWindow &window);
    void changePos();
};

}


#endif
