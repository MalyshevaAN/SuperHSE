#include "login_scene.hpp"
#include <iostream>
#include "game.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"
#include "authentication_scene.hpp"
#include "sql.hpp"

namespace super_hse {

LoginScene::LoginScene() {
    // text init
    if (!font.loadFromFile("../assets/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // bigRectangle init
    get_texture_from_file("menu.png", bigRectanglePicture);
    bigRectangle.setTexture(bigRectanglePicture);

    // input boxes init
    usernameInputBox.setSize(sf::Vector2f(200, 50));
    usernameInputBox.setFillColor(activeInputBoxColor);

    usernameInputText.setFont(font);
    usernameInputText.setCharacterSize(24);
    usernameInputText.setFillColor(sf::Color::Black);

    usernameLabel.setFont(font);
    usernameLabel.setCharacterSize(24);
    usernameLabel.setFillColor(sf::Color::Black);
    usernameLabel.setString("Username: ");

    passwordInputBox.setSize(sf::Vector2f(200, 50));
    passwordInputBox.setFillColor(sf::Color::White);

    passwordInputText.setFont(font);
    passwordInputText.setCharacterSize(24);
    passwordInputText.setFillColor(sf::Color::Black);

    passwordLabel.setFont(font);
    passwordLabel.setCharacterSize(24);
    passwordLabel.setFillColor(sf::Color::Black);
    passwordLabel.setString("Password: ");

    // buttons init
    get_texture_from_file(
        "login_button.png", loginButtonPicture
    );
    loginButton.setTexture(loginButtonPicture);

    updateSceneSize();
}

void LoginScene::updateActiveInputText(const sf::Uint32 unicode) {
    if (unicode >= 128) {
        return;
    }

    std::string text = activeInputText->getString();
    if (unicode == 8) {  // backspace
        if (!text.empty()) {
            text.pop_back();
        }
    } else {
        text += static_cast<char>(unicode);
    }
    activeInputText->setString(text);
}

void LoginScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (loginButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                const std::string username = usernameInputText.getString();
                const std::string password = passwordInputText.getString();
                if (loginUser(username, password) == -1) {
                    std::cerr << "User not found\n";
                    return;
                }
                Game::player_id = loginUser(username, password);
                Game::player_name = username;
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
            if (usernameInputBox.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                activeInputText = &usernameInputText;
                usernameInputBox.setFillColor(activeInputBoxColor);
                passwordInputBox.setFillColor(sf::Color::White);
            }
            if (passwordInputBox.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                activeInputText = &passwordInputText;
                usernameInputBox.setFillColor(sf::Color::White);
                passwordInputBox.setFillColor(activeInputBoxColor);
            }
            if (Game::backButton.getGlobalBounds().contains(
                event.mouseButton.x, event.mouseButton.y
            )) {
                SceneManager::changeScene(std::make_unique<AuthenticationScene>());
            }
        }
    }
    if (event.type == sf::Event::TextEntered) {
        updateActiveInputText(event.text.unicode);
    }
}

void LoginScene::update(sf::Time &dTime) {
}

void LoginScene::updateSceneSize() {
    // update positions of all objects
    bigRectangle.setPosition(
        (Game::windowWidth - bigRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - bigRectanglePicture.getSize().y) / 2 - 125
    );

    usernameInputBox.setPosition(
        (Game::windowWidth - usernameInputBox.getSize().x) / 2,
        (Game::windowHeight - usernameInputBox.getSize().y) / 2
    );
    usernameInputText.setPosition(
        (Game::windowWidth - usernameInputBox.getSize().x) / 2 + 10,
        (Game::windowHeight - usernameInputBox.getSize().y) / 2 + 10
    );
    usernameLabel.setPosition(
        (Game::windowWidth - usernameInputBox.getSize().x) / 2 - 125,
        (Game::windowHeight - usernameInputBox.getSize().y) / 2 + 10
    );

    passwordInputBox.setPosition(
        (Game::windowWidth - passwordInputBox.getSize().x) / 2,
        (Game::windowHeight - passwordInputBox.getSize().y) / 2 + 100
    );
    passwordInputText.setPosition(
        (Game::windowWidth - passwordInputBox.getSize().x) / 2 + 10,
        (Game::windowHeight - passwordInputBox.getSize().y) / 2 + 110
    );
    passwordLabel.setPosition(
        (Game::windowWidth - passwordInputBox.getSize().x) / 2 - 125,
        (Game::windowHeight - passwordInputBox.getSize().y) / 2 + 110
    );

    loginButton.setPosition(
        (Game::windowWidth - loginButtonPicture.getSize().x) / 2,
        (Game::windowHeight - loginButtonPicture.getSize().y) / 2 + 200
    );
}

void LoginScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);

    window.draw(usernameInputBox);
    window.draw(usernameInputText);
    window.draw(usernameLabel);

    window.draw(passwordInputBox);
    window.draw(passwordInputText);
    window.draw(passwordLabel);

    window.draw(loginButton);
    window.draw(Game::backButton);
    window.display();
}

}  // namespace super_hse
