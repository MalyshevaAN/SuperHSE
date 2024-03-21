#include "game.hpp"
#include "authentication_scene.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"

namespace super_hse {

AuthenticationScene::AuthenticationScene() {
    // bigRectangle init
    get_texture_from_file("menu.png", bigRectanglePicture);
    bigRectangle.setTexture(bigRectanglePicture);

    // buttons init
    get_texture_from_file("authentication_play_button.png", buttonPlayPicture);
    buttonPlay.setTexture(buttonPlayPicture);

    // text init
    if (!font.loadFromFile("../assets/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
    }
    text.setFont(font);
    text.setString(
        "Here some authentication logic should be added\n"
    );
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(150, 10);

    updateSceneSize();
}

void AuthenticationScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (buttonPlay.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
        }
    }


}

void AuthenticationScene::update(sf::Time &dTime) {

}

void AuthenticationScene::updateSceneSize() {
    // update positions of all objects
    bigRectangle.setPosition(
        (Game::windowWidth - bigRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - bigRectanglePicture.getSize().y) / 2 - 50
    );

    buttonPlay.setPosition(
        (Game::windowWidth - buttonPlayPicture.getSize().x) / 2,
        (Game::windowHeight - buttonPlayPicture.getSize().y) / 2 + 200
    );
}

void AuthenticationScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);
    window.draw(buttonPlay);
    window.draw(text);
    window.display();
}

}  // namespace super_hse
