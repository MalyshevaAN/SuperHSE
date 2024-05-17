#ifndef INPUT_BOX_HPP_
#define INPUT_BOX_HPP_

#include <SFML/Graphics.hpp>
#include <string>

namespace super_hse {

enum class InputBoxType { Username, Password, PasswordAgain, IP, Port};

class InputBox {
public:
    std::string textString;
    sf::RectangleShape box;
    sf::Text inputText;
    sf::Text label;
    bool mustBeHidden = false;
    InputBoxType type;

    sf::RectangleShape cursor;
    int cursorPosition = 0;
    float cursorTimer = 0;
    float cursorSpeed = 0.001f;
    const float cursorResetTime = 0.5f;
    bool cursorVisible = false;

    void init(const sf::Font &font, const InputBoxType box_type);
    void draw(sf::RenderWindow &window);
    void setPosition();
    void updateText(const sf::Uint32 unicode);
    void update(sf::Time &dTime);
    void updateCursorPosition(sf::Event &event);
};

class ErrorBox {
public:
    sf::Text errorText;
    sf::RectangleShape box;

    int heightOffset;

    const sf::Color defaultColor = sf::Color(154, 217, 234);
    const sf::Color errorColor = sf::Color(255, 152, 179);
    const sf::Color errorTextColor = sf::Color(57, 8, 18);
    sf::Color currentColor = defaultColor;

    void init(const sf::Font &font, const int newHeightOffset);
    void draw(sf::RenderWindow &window);
    void setPosition();
    void clear();
    void setError(const std::string &error);
};

}  // namespace super_hse

#endif  // INPUT_BOX_HPP_
