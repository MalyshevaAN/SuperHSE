#include "input_box.hpp"
#include "game.hpp"

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
    } else if (type == InputBoxType::Password) {
        label.setString("Password: ");
        mustBeHidden = true;
    } else {
        label.setString("Password again: ");
        mustBeHidden = true;
    }
}

void InputBox::setPosition() {
    int type_offset;
    if (type == InputBoxType::Username) {
        type_offset = 0;
    } else if (type == InputBoxType::Password) {
        type_offset = 75;
    } else {
        type_offset = 150;
    }
    const int center_x = (Game::windowWidth - box.getSize().x) / 2;
    const int center_y = (Game::windowHeight - box.getSize().y) / 2;

    const int padding = 10;
    const int leftMarginLabel = label.getGlobalBounds().width;

    box.setPosition(center_x, center_y + type_offset);
    inputText.setPosition(center_x + padding, center_y + padding + type_offset);
    label.setPosition(
        center_x - leftMarginLabel, center_y + padding + type_offset
    );
}

void InputBox::draw(sf::RenderWindow &window) {
    window.draw(box);
    window.draw(inputText);
    window.draw(label);
}

}  // namespace super_hse