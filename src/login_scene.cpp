#include "game.hpp"
#include "login_scene.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"
#include <iostream>

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
    usernameInputBox.setFillColor(sf::Color::White);
    usernameInputText.setFont(font);
    usernameInputText.setCharacterSize(24);
    usernameInputText.setFillColor(sf::Color::Black);

    passwordInputBox.setSize(sf::Vector2f(200, 50));
    passwordInputBox.setFillColor(sf::Color::White);
    passwordInputText.setFont(font);
    passwordInputText.setCharacterSize(24);
    passwordInputText.setFillColor(sf::Color::Black);

    // buttons init
    get_texture_from_file("authentication_login_button.png", loginButtonPicture);
    loginButton.setTexture(loginButtonPicture);

    updateSceneSize();
}

void LoginScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (loginButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                // TODO ВОТ ТУТ НАДО ПРИКРУТИТЬ РАБОТУ С БДШКОЙ
                std::string username = usernameInputText.getString();
                std::string password = passwordInputText.getString();
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
            if (usernameInputBox.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                activeInputText = &usernameInputText;
            }
            if (passwordInputBox.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
            )) {
                activeInputText = &passwordInputText;
            }
        }
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 128) {
            return;
        }

        std::string text = activeInputText->getString();
        if (event.text.unicode == 8) {  // backspace
            if (text.size() > 0) {
                text.pop_back();
            }
        } else {
            text += static_cast<char>(event.text.unicode);
        }
        activeInputText->setString(text);
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

    passwordInputBox.setPosition(
        (Game::windowWidth - passwordInputBox.getSize().x) / 2,
        (Game::windowHeight - passwordInputBox.getSize().y) / 2 + 100
    );
    passwordInputText.setPosition(
        (Game::windowWidth - passwordInputBox.getSize().x) / 2 + 10,
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
    window.draw(passwordInputBox);
    window.draw(passwordInputText);

    window.draw(loginButton);
    window.display();
}

}  // namespace super_hse
