#include "authentication_scene.hpp"
#include <iostream>
#include "game.hpp"
#include "login_scene.hpp"
#include "register_scene.hpp"
#include "scene.hpp"

namespace super_hse {

AuthenticationScene::AuthenticationScene() {
    // bigRectangle init
    get_texture_from_file("menu.png", bigRectanglePicture);
    bigRectangle.setTexture(bigRectanglePicture);

    // buttons init
    get_texture_from_file(
        "authentication_login_button.png", loginButtonPicture
    );
    loginButton.setTexture(loginButtonPicture);

    get_texture_from_file(
        "authentication_register_button.png", registerButtonPicture
    );
    registerButton.setTexture(registerButtonPicture);

    updateSceneSize();
}

void AuthenticationScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (loginButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                ;
                SceneManager::changeScene(std::make_unique<LoginScene>());
                return;
            }
            if (registerButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<RegisterScene>());
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
        (Game::windowHeight - bigRectanglePicture.getSize().y) / 2 - 125
    );

    loginButton.setPosition(
        (Game::windowWidth - loginButtonPicture.getSize().x) / 2,
        (Game::windowHeight - loginButtonPicture.getSize().y) / 2 + 100
    );

    registerButton.setPosition(
        (Game::windowWidth - registerButtonPicture.getSize().x) / 2,
        (Game::windowHeight - registerButtonPicture.getSize().y) / 2 + 200
    );
}

void AuthenticationScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);

    window.draw(loginButton);
    window.draw(registerButton);

    window.display();
}

}  // namespace super_hse
