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
    usernameInputBox.setPosition(
        (Game::windowWidth - usernameInputBox.getSize().x) / 2,
        (Game::windowHeight - usernameInputBox.getSize().y) / 2
    );

    usernameInputText.setFont(font);
    usernameInputText.setCharacterSize(24);
    usernameInputText.setFillColor(sf::Color::Black);
    usernameInputText.setPosition(
        (Game::windowWidth - usernameInputBox.getSize().x) / 2 + 10,
        (Game::windowHeight - usernameInputBox.getSize().y) / 2 + 10
    );


    // buttons init
    get_texture_from_file("authentication_login_button.png", loginButtonPicture);
    loginButton.setTexture(loginButtonPicture);


    playerUsername.setFont(font);
    playerUsername.setString("Player name: " + Game::player_name);
    playerUsername.setCharacterSize(24);
    playerUsername.setFillColor(sf::Color::Black);
    playerUsername.setPosition(150, 30);

    updateSceneSize();
}

void LoginScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (loginButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
            if (usernameInputBox.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                activeInputText = &usernameInputText;
            }

        }
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 128) {
            return;
        }

        std::string text = activeInputText->getString();
        if (event.text.unicode == 8) {
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

    loginButton.setPosition(
        (Game::windowWidth - loginButtonPicture.getSize().x) / 2,
        (Game::windowHeight - loginButtonPicture.getSize().y) / 2 + 200
    );

    playerUsername.setPosition(
        (Game::windowWidth - playerUsername.getLocalBounds().width) / 2,
        (Game::windowHeight - playerUsername.getLocalBounds().height) / 2 + 100
    );
}

void LoginScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);
    window.draw(playerUsername);

    window.draw(usernameInputBox);
    window.draw(usernameInputText);

    window.draw(loginButton);
    window.display();
}

}  // namespace super_hse
