#include "register_scene.hpp"
#include "authentication_scene.hpp"
#include "game.hpp"
#include "sql.hpp"

namespace super_hse {

RegisterScene::RegisterScene() {
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
    passwordAgainInput.init(font, InputBoxType::PasswordAgain);

    usernameInput.box.setFillColor(activeInputBoxColor);

    // buttons init
    get_texture_from_file("create_user_button.png", createPlayerButtonPicture);
    createPlayerButton.setTexture(createPlayerButtonPicture);

    updateSceneSize();
}

void RegisterScene::updateActiveInputText(const sf::Uint32 unicode) {
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
    if (activeInputBox->mustBeHidden) {
        activeInputBox->inputText.setString(std::string(text.size(), '*'));
    } else {
        activeInputBox->inputText.setString(text);
    }
}

void RegisterScene::updateInputBoxes(sf::Event &event) {
    if (usernameInput.box.getGlobalBounds().contains(
            event.mouseButton.x, event.mouseButton.y
        )) {
        activeInputBox = &usernameInput;
        usernameInput.box.setFillColor(activeInputBoxColor);
        passwordInput.box.setFillColor(sf::Color::White);
        passwordAgainInput.box.setFillColor(sf::Color::White);
    }
    if (passwordInput.box.getGlobalBounds().contains(
            event.mouseButton.x, event.mouseButton.y
        )) {
        activeInputBox = &passwordInput;
        usernameInput.box.setFillColor(sf::Color::White);
        passwordInput.box.setFillColor(activeInputBoxColor);
        passwordAgainInput.box.setFillColor(sf::Color::White);
    }
    if (passwordAgainInput.box.getGlobalBounds().contains(
            event.mouseButton.x, event.mouseButton.y
        )) {
        activeInputBox = &passwordAgainInput;
        usernameInput.box.setFillColor(sf::Color::White);
        passwordInput.box.setFillColor(sf::Color::White);
        passwordAgainInput.box.setFillColor(activeInputBoxColor);
    }
}

void RegisterScene::checkAndChangeScene() {
    const std::string username = usernameInput.textString;
    const std::string password = passwordInput.textString;
    const std::string passwordAgain = passwordAgainInput.textString;

    // TODO: выводить ошибки на окне
    if (!registerUser(username, password)) {
        std::cerr << "Error registering user\n";
        return;
    }

    registerUser(username, password);
    SceneManager::changeScene(std::make_unique<AuthenticationScene>());
}

void RegisterScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (createPlayerButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                checkAndChangeScene();
                return;
            }

            updateInputBoxes(event);

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

void RegisterScene::update(sf::Time &dTime) {
}

void RegisterScene::updateSceneSize() {
    // update positions of all objects
    bigRectangle.setPosition(
        (Game::windowWidth - bigRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - bigRectanglePicture.getSize().y) / 2 - 125
    );

    usernameInput.setPosition();
    passwordInput.setPosition();
    passwordAgainInput.setPosition();

    createPlayerButton.setPosition(
        (Game::windowWidth - createPlayerButtonPicture.getSize().x) / 2,
        (Game::windowHeight - createPlayerButtonPicture.getSize().y) / 2 + 300
    );
}

void RegisterScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);

    usernameInput.draw(window);
    passwordInput.draw(window);
    passwordAgainInput.draw(window);

    window.draw(createPlayerButton);
    window.draw(Game::backButton);
    window.display();
}

}  // namespace super_hse
