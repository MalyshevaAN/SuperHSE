#ifndef WARDROBE_SCENE_HPP_
#define WARDROBE_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse {

class WardrobeScene : public Scene {
private:
// TODO vectors
    sf::Texture skin1Texture;
    sf::Texture skin2Texture;
    sf::Texture skin3Texture;
    sf::Texture skin4Texture;
    sf::Texture skin5Texture;
    sf::Texture skin6Texture;

    sf::Sprite skin1;
    sf::Sprite skin2;
    sf::Sprite skin3;
    sf::Sprite skin4;
    sf::Sprite skin5;
    sf::Sprite skin6;

    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public:
    WardrobeScene();
    
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // WARDROBE_SCENE_HPP_
