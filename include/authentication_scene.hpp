#ifndef AUTHENTICATION_SCENE_HPP_
#define AUTHENTICATION_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse {

class AuthenticationScene : public Scene {
private:
    sf::Texture bigRectanglePicture;
    sf::Sprite bigRectangle;

    sf::Texture loginButtonPicture;
    sf::Sprite loginButton;

    sf::Texture registerButtonPicture;
    sf::Sprite registerButton;

    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public:
    AuthenticationScene();

    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // AUTHENTICATION_SCENE_HPP_