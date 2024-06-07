#include "multi_connect_scene.hpp"
#include "game.hpp"
#include "input_box.hpp"
#include "main_menu_scene.hpp"
#include "multiplayer_scene.hpp"

namespace super_hse {

MultiConnectScene::MultiConnectScene() {
    if (!font.loadFromFile("../assets/fonts/8bit.ttf")) {
        std::cerr << "Error loading font\n";
    }

    get_texture_from_file("menu.png", bigRectanglePicture);
    bigRectangle.setTexture(bigRectanglePicture);

    ipInput.init(font, InputBoxType::IP);
    portInput.init(font, InputBoxType::Port);

    ipInput.box.setFillColor(activeInputBoxColor);
    ipInput.cursorVisible = true;

    const int errorBoxheightOffset = 150;
    errorBox.init(font, errorBoxheightOffset);

    get_texture_from_file("connect_button.png", connectButtonPicture);
    connectButton.setTexture(connectButtonPicture);

    updateSceneSize();
}

void MultiConnectScene::updateActiveInputText(const sf::Uint32 unicode) {
    activeInputBox->updateText(unicode);
    std::string &text = activeInputBox->textString;

    activeInputBox->inputText.setString(text);
}

void MultiConnectScene::updateInputBoxes(sf::Event &event) {
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
    activeInputBox->box.setFillColor(sf::Color::White);
    activeInputBox->cursorVisible = false;

    activeInputBox = inputBoxes[activeInputBoxIndex];

    activeInputBox->box.setFillColor(activeInputBoxColor);
    activeInputBox->cursorVisible = true;
}

void MultiConnectScene::checkAndConnect() {
    const std::string IP = ipInput.textString;
    const std::string port = portInput.textString;  //

    // TODO всякие проверки на валидность айпи и порта
    if (true) {
        errorBox.setError("IP and port are checked");
        SceneManager::changeScene(
            std::make_unique<MultiLevelScene>(IP, std::stoi(port), 1)
        );
        // return;
    }
    // TODO подключение к серверу и смена сцены
    // SceneManager::changeScene(std::make_unique<...>());
}

void MultiConnectScene::handleInput(sf::Event &event) {
    updateInputBoxes(event);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (connectButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                checkAndConnect();
                return;
            }
            if (Game::backButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            checkAndConnect();
        }
    }
    if (event.type == sf::Event::TextEntered) {
        updateActiveInputText(event.text.unicode);
    }
}

void MultiConnectScene::update(sf::Time &dTime) {
    activeInputBox->update(dTime);
}

void MultiConnectScene::updateSceneSize() {
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

    ipInput.setPosition();
    portInput.setPosition();
    errorBox.setPosition();

    connectButton.setPosition(
        (Game::windowWidth - connectButtonPicture.getSize().x) / 2,
        (Game::windowHeight - connectButtonPicture.getSize().y) / 2 + 225
    );
}

void MultiConnectScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);

    ipInput.draw(window);
    portInput.draw(window);
    errorBox.draw(window);

    window.draw(connectButton);
    window.draw(Game::backButton);
    window.draw(Game::soundButton);

    window.display();
}

}  // namespace super_hse
