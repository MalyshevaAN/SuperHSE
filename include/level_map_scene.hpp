#ifndef LEVEL_MAP_SCENE_HPP_
#define LEVEL_MAP_SCENE_HPP_


#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse {

class LevelMapScene : public Scene {
private:
    sf::Texture buttonLevel1Picture;
    sf::Sprite buttonLevel1;

    const sf::Color backgroundColor = sf::Color(114, 134, 207);

public:
    LevelMapScene();
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
};

}  // namespace super_hse

#endif // LEVEL_MAP_SCENE_HPP_
