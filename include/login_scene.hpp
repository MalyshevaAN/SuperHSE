#ifndef LOGIN_SCENE_HPP_
#define LOGIN_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "input_box.hpp"
#include "scene.hpp"

namespace super_hse {

class LoginScene : public Scene {
private:
    sf::Texture bigRectanglePicture;
    sf::Sprite bigRectangle;

    InputBox usernameInput;
    InputBox passwordInput;
    InputBox *activeInputBox = &usernameInput;
    std::vector<InputBox *> inputBoxes = {&usernameInput, &passwordInput};
    int activeInputBoxIndex = 0;

    ErrorBox errorBox;

    sf::Texture loginButtonPicture;
    sf::Sprite loginButton;

    sf::Font font;

    const sf::Color backgroundColor = sf::Color(154, 217, 234);
    const sf::Color activeInputBoxColor = sf::Color(219, 219, 219);

public:
    LoginScene();

    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;

    void updateActiveInputText(const sf::Uint32 unicode);
    void updateInputBoxes(sf::Event &event);
    void checkAndChangeScene();
};

}  // namespace super_hse

#endif  // LOGIN_SCENE_HPP_