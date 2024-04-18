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
    usernameInput.init(font, InputBoxType::Username);
    passwordInput.init(font, InputBoxType::Password);

    usernameInput.box.setFillColor(activeInputBoxColor);

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

    std::string text = activeInputBox->inputText.getString();
    if (unicode == 8) {  // backspace
        if (!text.empty()) {
            text.pop_back();
        }
    } else {
        text += static_cast<char>(unicode);
    }
    activeInputBox->inputText.setString(text);
}


void LoginScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (loginButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                const std::string username = usernameInput.inputText.getString();
                const std::string password = passwordInput.inputText.getString();
                if (loginUser(username, password) == -1) {
                    std::cerr << "User not found\n";
                    return;
                }
                Game::player_id = loginUser(username, password);
                Game::player_name = username;
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }

            if (usernameInput.box.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                activeInputBox = &usernameInput;
                usernameInput.box.setFillColor(activeInputBoxColor);
                passwordInput.box.setFillColor(sf::Color::White);
            }
            if (passwordInput.box.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                activeInputBox = &passwordInput;
                usernameInput.box.setFillColor(sf::Color::White);
                passwordInput.box.setFillColor(activeInputBoxColor);
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

    usernameInput.box.setPosition(
        (Game::windowWidth - usernameInput.box.getSize().x) / 2,
        (Game::windowHeight - usernameInput.box.getSize().y) / 2
    );
    usernameInput.inputText.setPosition(
        (Game::windowWidth - usernameInput.box.getSize().x) / 2 + 10,
        (Game::windowHeight - usernameInput.box.getSize().y) / 2 + 10
    );
    usernameInput.label.setPosition(
        (Game::windowWidth - usernameInput.box.getSize().x) / 2 - 125,
        (Game::windowHeight - usernameInput.box.getSize().y) / 2 + 10
    );

    passwordInput.box.setPosition(
        (Game::windowWidth - passwordInput.box.getSize().x) / 2,
        (Game::windowHeight - passwordInput.box.getSize().y) / 2 + 100
    );
    passwordInput.inputText.setPosition(
        (Game::windowWidth - passwordInput.box.getSize().x) / 2 + 10,
        (Game::windowHeight - passwordInput.box.getSize().y) / 2 + 110
    );
    passwordInput.label.setPosition(
        (Game::windowWidth - passwordInput.box.getSize().x) / 2 - 125,
        (Game::windowHeight - passwordInput.box.getSize().y) / 2 + 110
    );

    loginButton.setPosition(
        (Game::windowWidth - loginButtonPicture.getSize().x) / 2,
        (Game::windowHeight - loginButtonPicture.getSize().y) / 2 + 200
    );
}

void LoginScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);

    window.draw(usernameInput.box);
    window.draw(usernameInput.inputText);
    window.draw(usernameInput.label);

    window.draw(passwordInput.box);
    window.draw(passwordInput.inputText);
    window.draw(passwordInput.label);

    window.draw(loginButton);
    window.draw(Game::backButton);
    window.display();
}

}  // namespace super_hse
