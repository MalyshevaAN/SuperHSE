#include "login_scene.hpp"
#include <iostream>
#include "authentication_scene.hpp"
#include "game.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"
#include "sql.hpp"

namespace super_hse {

LoginScene::LoginScene() {
    // text init
    if (!font.loadFromFile("../assets/fonts/8bit.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // bigRectangle init
    get_texture_from_file("menu.png", bigRectanglePicture);
    bigRectangle.setTexture(bigRectanglePicture);

    // input boxes init
    usernameInput.init(font, InputBoxType::Username);
    passwordInput.init(font, InputBoxType::Password);

    usernameInput.box.setFillColor(activeInputBoxColor);
    usernameInput.cursorVisible = true;

    const int errorBoxheightOffset = 150;
    errorBox.init(font, errorBoxheightOffset);

    // buttons init
    get_texture_from_file("login_button.png", loginButtonPicture);
    loginButton.setTexture(loginButtonPicture);

    updateSceneSize();
}

void LoginScene::updateActiveInputText(const sf::Uint32 unicode) {
    activeInputBox->updateText(unicode);
    std::string &text = activeInputBox->textString;

    if (activeInputBox->mustBeHidden) {
        activeInputBox->inputText.setString(std::string(text.size(), '*'));
    } else {
        activeInputBox->inputText.setString(text);
    }
}

void LoginScene::updateInputBoxes(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Down) {
            activeInputBoxIndex = (activeInputBoxIndex + 1) % inputBoxes.size();

        } else if (event.key.code == sf::Keyboard::Up) {
            activeInputBoxIndex =
                (activeInputBoxIndex - 1 + inputBoxes.size()) %
                inputBoxes.size();

        } else {
            activeInputBox->updateCursorPosition(event);
        }
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (int index = 0; index < inputBoxes.size(); index++) {
                if (inputBoxes[index]->box.getGlobalBounds().contains(
                        event.mouseButton.x, event.mouseButton.y
                    )) {
                    activeInputBoxIndex = index;
                }
            }
        }
    } else {
        return;
    }
    for (auto &inputBox : inputBoxes) {
        inputBox->box.setFillColor(sf::Color::White);
        inputBox->cursorVisible = false;
    }
    activeInputBox = inputBoxes[activeInputBoxIndex];
    activeInputBox->box.setFillColor(activeInputBoxColor);
    activeInputBox->cursorVisible = true;
}

void LoginScene::checkAndChangeScene() {
    const std::string username = usernameInput.textString;
    const std::string password = passwordInput.textString;

    if (username.empty()) {
        errorBox.setError("Username cannot be empty!");
        return;
    }
    if (password.empty()) {
        errorBox.setError("Password cannot be empty!");
        return;
    }
    if (loginUser(username, password) == -1) {
        errorBox.setError("Username or password is incorrect!");
        return;
    }

    Game::player_id = loginUser(username, password);
    Game::player_name = username;
    SceneManager::changeScene(std::make_unique<MainMenuScene>());
}

void LoginScene::handleInput(sf::Event &event) {
    updateInputBoxes(event);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (loginButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                checkAndChangeScene();
                return;
            }

            if (Game::backButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<AuthenticationScene>(
                ));
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            checkAndChangeScene();
        }
    }
    if (event.type == sf::Event::TextEntered) {
        updateActiveInputText(event.text.unicode);
    }
}

void LoginScene::update(sf::Time &dTime) {
    activeInputBox->update(dTime);
}

void LoginScene::updateSceneSize() {
    Game::backButton.setPosition(20, 20);
    Game::soundButton.setPosition(
        Game::backButton.getPosition().x +
            Game::backButton.getGlobalBounds().width + 20,
        20
    );

    bigRectangle.setPosition(
        (Game::windowWidth - bigRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - bigRectanglePicture.getSize().y) / 2 - 125
    );

    usernameInput.setPosition();
    passwordInput.setPosition();
    errorBox.setPosition();

    loginButton.setPosition(
        (Game::windowWidth - loginButtonPicture.getSize().x) / 2,
        (Game::windowHeight - loginButtonPicture.getSize().y) / 2 + 225
    );
}

void LoginScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);

    usernameInput.draw(window);
    passwordInput.draw(window);
    errorBox.draw(window);

    window.draw(loginButton);
    window.draw(Game::backButton);
    window.draw(Game::soundButton);

    window.display();
}

}  // namespace super_hse
