#ifndef LOSE_SCENE_HPP
#define LOSE_SCENE_HPP

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse{
class LoseScene : public Scene {
private:
    sf::Texture backgroundTexture;
    sf::Texture mainMenuTexture;
    sf::Texture tryAgainTexture;
    sf::Sprite mainMenu;
    sf::Sprite tryAgain;
    sf::Sprite background;

    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public:
    LoseScene();
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;

};
}

#endif
