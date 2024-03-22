#include "register_scene.hpp"
#include "authentication_scene.hpp"
#include "game.hpp"

namespace super_hse {

RegisterScene::RegisterScene() {
    // bigRectangle init
    get_texture_from_file("menu.png", bigRectanglePicture);
    bigRectangle.setTexture(bigRectanglePicture);

    // buttons init
    get_texture_from_file("create_user.png", createPlayerButtonPicture);
    createPlayerButton.setTexture(createPlayerButtonPicture);

    updateSceneSize();
}

void RegisterScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (createPlayerButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<AuthenticationScene>());
                return;
            }
        }
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

    createPlayerButton.setPosition(
        (Game::windowWidth - createPlayerButtonPicture.getSize().x) / 2,
        (Game::windowHeight - createPlayerButtonPicture.getSize().y) / 2 + 50
    );
}

void RegisterScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);
    window.draw(createPlayerButton);
    window.display();
}

}  // namespace super_hse
