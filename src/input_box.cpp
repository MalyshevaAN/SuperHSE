#include "input_box.hpp"

namespace super_hse {

void InputBox::init(const sf::Font &font, const InputBoxType box_type) {
    type = box_type;
    
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

}