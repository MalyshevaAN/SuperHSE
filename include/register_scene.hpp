#ifndef REGISTER_SCENE_HPP_
#define REGISTER_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse {

class RegisterScene : public Scene {
private:
    sf::Texture bigRectanglePicture;
    sf::Sprite bigRectangle;

    sf::Texture createPlayerButtonPicture;
    sf::Sprite createPlayerButton;

    sf::Font font;
    sf::Text playerUsername;
    
    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public :
    RegisterScene();

    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // REGISTER_SCENE_HPP_