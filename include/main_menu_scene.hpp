#ifndef MAIN_MENU_SCENE_HPP_
#define MAIN_MENU_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse {

class MainMenuScene : public Scene {
private:
    sf::Texture bigRectanglePicture;
    sf::Sprite bigRectangle;

    sf::Texture buttonSingleplayerPicture;
    sf::Texture buttonMultiplayerPicture;
    sf::Sprite buttonSingleplayer;
    sf::Sprite buttonMultiplayer;

    sf::Font font;
    sf::Text text;
    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public:
    MainMenuScene();

    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // MAIN_MENU_SCENE_HPP_