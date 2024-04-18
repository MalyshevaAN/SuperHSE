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
    int type_offset = (type == InputBoxType::Username ? 0 : 100);

    box.setPosition(
        (Game::windowWidth - box.getSize().x) / 2,
        (Game::windowHeight - box.getSize().y) / 2 + type_offset
    );
    inputText.setPosition(
        (Game::windowWidth - box.getSize().x) / 2 + 10,
        (Game::windowHeight - box.getSize().y) / 2 + 10 + type_offset
    );
    label.setPosition(
        (Game::windowWidth - box.getSize().x) / 2 - 125,
        (Game::windowHeight - box.getSize().y) / 2 + 10 + type_offset
    );
}

void InputBox::draw(sf::RenderWindow &window) {
    window.draw(box);
    window.draw(inputText);
    window.draw(label);
}

}