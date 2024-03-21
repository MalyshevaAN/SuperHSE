#include "game.hpp"
#include "authentication_scene.hpp"
#include "scene.hpp"

namespace super_hse {

AuthenticationScene::AuthenticationScene() {
    // bigRectangle init
    get_texture_from_file("menu.png", bigRectanglePicture);
    bigRectangle.setTexture(bigRectanglePicture);

    // buttons init
    // get_texture_from_file("singleplayer_button.png", buttonSingleplayerPicture);
    // buttonSingleplayer.setTexture(buttonSingleplayerPicture);

    // get_texture_from_file("multiplayer_button.png", buttonMultiplayerPicture);
    // buttonMultiplayer.setTexture(buttonMultiplayerPicture);

    updateSceneSize();
}

void AuthenticationScene::handleInput(sf::Event &event) {

}

void AuthenticationScene::update(sf::Time &dTime) {

}

void AuthenticationScene::updateSceneSize() {

}

void AuthenticationScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);
    // window.draw(buttonSingleplayer);
    // window.draw(buttonMultiplayer);
}

}  // namespace super_hse
