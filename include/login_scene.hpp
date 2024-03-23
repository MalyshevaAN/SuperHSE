#ifndef LOGIN_SCENE_HPP_
#define LOGIN_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse {

enum class InputBoxType {
    Username,
    Password
};

class LoginScene : public Scene {
private:
    sf::Texture bigRectanglePicture;
    sf::Sprite bigRectangle;

    sf::RectangleShape usernameInputBox;
    sf::Text usernameInputText;
    sf::RectangleShape passwordInputBox;
    sf::Text passwordInputText;

    sf::Text *activeInputText = &usernameInputText;

    sf::Texture loginButtonPicture;
    sf::Sprite loginButton;

    sf::Font font;
    sf::Text playerUsername;
    
    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public :
    LoginScene();

    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // LOGIN_SCENE_HPP_