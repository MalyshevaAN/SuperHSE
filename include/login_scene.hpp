#ifndef LOGIN_SCENE_HPP_
#define LOGIN_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse {

enum class InputBoxType { Username, Password };

class InputBox {
public:
    sf::RectangleShape box;
    sf::Text inputText;
    sf::Text label;
    bool mustBeHidden = false;

    void init(const sf::Font &font, const InputBoxType type) {
        box.setSize(sf::Vector2f(200, 50));
        box.setFillColor(sf::Color::White);

        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::Black);
        inputText.setFont(font);

        label.setCharacterSize(24);
        label.setFillColor(sf::Color::Black);
        label.setFont(font);

        if (type == InputBoxType::Username) {
            label.setString("Username: ");
        } else {
            label.setString("Password: ");
            mustBeHidden = true;
        }
    }
};

class LoginScene : public Scene {
private:
    sf::Texture bigRectanglePicture;
    sf::Sprite bigRectangle;

    InputBox usernameInput;
    InputBox passwordInput;
    InputBox *activeInputBox = &usernameInput;

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
    void updateInputBoxes();
};

}  // namespace super_hse

#endif  // LOGIN_SCENE_HPP_