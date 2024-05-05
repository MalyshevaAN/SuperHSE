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

    cursor.setSize(sf::Vector2f(2, 24));
    cursor.setFillColor(sf::Color::Black);

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
    cursor.setPosition(
        center_x + padding + inputText.getGlobalBounds().width,
        center_y + padding + type_offset
    );
}

void InputBox::updateText(const sf::Uint32 unicode) {
    if (unicode >= 128) {
        return;
    }

    if (unicode == 8) {  // backspace
        if (cursorPosition > 0) {
            textString.erase(cursorPosition - 1, 1);
            cursorPosition--;
        }
    } else {
        textString.insert(cursorPosition, 1, static_cast<char>(unicode));
        cursorPosition++;
    }
}

void InputBox::draw(sf::RenderWindow &window) {
    window.draw(box);
    window.draw(inputText);
    if (cursorVisible) {
        window.draw(cursor);
    }
    window.draw(label);
}

void InputBox::update(sf::Time &dTime) {
    cursorTimer += dTime.asMilliseconds() * cursorSpeed;
    if (cursorTimer >= cursorResetTime) {
        cursorVisible = !cursorVisible;
        cursorTimer = 0;
    }

    // cursor must be after first cursorPosition characters
    cursor.setPosition(
        inputText.findCharacterPos(cursorPosition).x,
        inputText.getPosition().y
    );
}

void InputBox::updateCursorPosition(sf::Event &event) {
    if (event.key.code == sf::Keyboard::Left) {
        cursorPosition = std::max(0, cursorPosition - 1);

    } else if (event.key.code == sf::Keyboard::Right) {
        cursorPosition = std::min(
            static_cast<int>(textString.size()), cursorPosition + 1
        );

    } else if (event.key.code == sf::Keyboard::Home) {
        cursorPosition = 0;
        
    } else if (event.key.code == sf::Keyboard::End) {
        cursorPosition = textString.size();
    }
}

void ErrorBox::init(const sf::Font &font, const int newHeightOffset) {
    errorText.setCharacterSize(24);
    errorText.setFillColor(errorTextColor);
    errorText.setFont(font);

    box.setSize(sf::Vector2f(400, 50));
    box.setFillColor(defaultColor);

    heightOffset = newHeightOffset;

    setPosition();
}

void ErrorBox::setPosition() {
    const int box_x = (Game::windowWidth - box.getSize().x) / 2;
    const int box_y = (Game::windowHeight - box.getSize().y) / 2;
    box.setPosition(box_x, box_y + heightOffset);

    const int padding = 10;
    const int text_x = (Game::windowWidth - errorText.getGlobalBounds().width) / 2;
    errorText.setPosition(text_x, box_y + padding + heightOffset);
}

void ErrorBox::clear() {
    errorText.setString("");
    box.setFillColor(defaultColor);
    setPosition();
}

void ErrorBox::draw(sf::RenderWindow &window) {
    window.draw(box);
    window.draw(errorText);
}

void ErrorBox::setError(const std::string &error) {
    errorText.setString(error);
    box.setFillColor(errorColor);
    setPosition();
}

}  // namespace super_hse