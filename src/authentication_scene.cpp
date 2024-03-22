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
    get_texture_from_file("authentication_login_button.png", loginButtonPicture);
    loginButton.setTexture(loginButtonPicture);

    get_texture_from_file("authentication_register_button.png", registerButtonPicture);
    registerButton.setTexture(registerButtonPicture);

    // text init
    if (!font.loadFromFile("../assets/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
    }
    playerUsername.setFont(font);
    playerUsername.setString("Player name: " + Game::player_name);
    playerUsername.setCharacterSize(24);
    playerUsername.setFillColor(sf::Color::Black);
    playerUsername.setPosition(150, 30);

    updateSceneSize();
}

void AuthenticationScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // TODO handle buttons click

            // if (buttonPlay.getGlobalBounds().contains(
            //         event.mouseButton.x, event.mouseButton.y
            //     )) {
            //     // TODO check if player is authenticated
            //     SceneManager::changeScene(std::make_unique<MainMenuScene>());
            //     return;
            // }
        }
    }


}

void AuthenticationScene::update(sf::Time &dTime) {

}

void AuthenticationScene::updateSceneSize() {
    // update positions of all objects
    bigRectangle.setPosition(
        (Game::windowWidth - bigRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - bigRectanglePicture.getSize().y) / 2 - 125
    );

    loginButton.setPosition(
        (Game::windowWidth - loginButtonPicture.getSize().x) / 2,
        (Game::windowHeight - loginButtonPicture.getSize().y) / 2 + 200
    );

    registerButton.setPosition(
        (Game::windowWidth - registerButtonPicture.getSize().x) / 2,
        (Game::windowHeight - registerButtonPicture.getSize().y) / 2 + 300
    );

    playerUsername.setPosition(
        (Game::windowWidth - playerUsername.getLocalBounds().width) / 2,
        (Game::windowHeight - playerUsername.getLocalBounds().height) / 2 + 100
    );
}

void AuthenticationScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);
    window.draw(loginButton);
    window.draw(registerButton);
    window.draw(playerUsername);
    window.display();
}

}  // namespace super_hse
