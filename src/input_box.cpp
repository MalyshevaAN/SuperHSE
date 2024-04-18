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
    } else {
        label.setString("Password: ");
        mustBeHidden = true;
    }
}

void InputBox::setPosition() {
    const int type_offset = (type == InputBoxType::Username ? 0 : 100);
    const int center_x = (Game::windowWidth - box.getSize().x) / 2;
    const int center_y = (Game::windowHeight - box.getSize().y) / 2;

    box.setPosition(center_x, center_y + type_offset);
    inputText.setPosition(center_x + 10, center_y + 10 + type_offset);
    label.setPosition(center_x - 125, center_y + 10 + type_offset);
}

void InputBox::draw(sf::RenderWindow &window) {
    window.draw(box);
    window.draw(inputText);
    window.draw(label);
}

}  // namespace super_hse