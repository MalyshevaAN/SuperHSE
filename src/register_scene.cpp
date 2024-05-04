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

    errorBox.init(font);

    // buttons init
    get_texture_from_file("create_user_button.png", createPlayerButtonPicture);
    createPlayerButton.setTexture(createPlayerButtonPicture);

    updateSceneSize();
}

void RegisterScene::updateActiveInputText(const sf::Uint32 unicode) {
    activeInputBox->updateText(unicode);
    std::string &text = activeInputBox->textString;
    
    if (activeInputBox->mustBeHidden) {
        activeInputBox->inputText.setString(std::string(text.size(), '*'));
    } else {
        activeInputBox->inputText.setString(text);
    }
}

void RegisterScene::checkAndChangeScene() {
    const std::string username = usernameInput.textString;
    const std::string password = passwordInput.textString;
    const std::string passwordAgain = passwordAgainInput.textString;

    if (password != passwordAgain) {
        errorBox.setError("Passwords do not match!");
        return;
    }
    if (!registerUser(username, password)) {
        errorBox.setError("Username already exists!");
        return;
    }

    registerUser(username, password);
    SceneManager::changeScene(std::make_unique<AuthenticationScene>());
}

void RegisterScene::updateInputBoxes(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Down) {
            activeInputBoxIndex = (activeInputBoxIndex + 1) % inputBoxes.size();
        }
        if (event.key.code == sf::Keyboard::Up) {
            activeInputBoxIndex =
                (activeInputBoxIndex - 1 + inputBoxes.size()) %
                inputBoxes.size();
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
    }
    for (auto &inputBox : inputBoxes) {
        inputBox->box.setFillColor(sf::Color::White);
    }
    activeInputBox = inputBoxes[activeInputBoxIndex];
    activeInputBox->box.setFillColor(activeInputBoxColor);
}

void RegisterScene::handleInput(sf::Event &event) {
    updateInputBoxes(event);
    
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
    errorBox.setPosition();

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
    errorBox.draw(window);

    window.draw(createPlayerButton);
    window.draw(Game::backButton);
    window.display();
}

}  // namespace super_hse
