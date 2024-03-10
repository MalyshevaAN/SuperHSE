#include "main_menu_scene.hpp"
#include <memory>
#include "game.hpp"
#include "level_map_scene.hpp"
#include "scene.hpp"

namespace super_hse {

MainMenuScene::MainMenuScene() {
    // bigRectangle init
    if (!bigRectanglePicture.loadFromFile("../assets/images/menu.png")) {
        std::cerr << "Error loading menu.png\n";
    }

    bigRectangle.setTexture(bigRectanglePicture);

    bigRectangle.setPosition(
        (Game::windowWidth - bigRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - bigRectanglePicture.getSize().y) / 2 - 50
    );

    // buttons init
    if (!buttonSingleplayerPicture.loadFromFile(
            "../assets/images/singleplayer_button.png"
        )) {
        std::cerr << "Error loading assets/images/singleplayer_button.png\n";
    }

    buttonSingleplayer.setTexture(buttonSingleplayerPicture);
    buttonSingleplayer.setPosition(
        (Game::windowWidth - buttonSingleplayerPicture.getSize().x) / 2,
        (Game::windowHeight - buttonSingleplayerPicture.getSize().y) / 2 + 50
    );

    if (!buttonMultiplayerPicture.loadFromFile(
            "../assets/images/multiplayer_button.png"
        )) {
        std::cerr << "Error loading assets/images/multiplayer_button.png.png\n";
    }

    buttonMultiplayer.setTexture(buttonMultiplayerPicture);
    buttonMultiplayer.setPosition(
        (Game::windowWidth - buttonMultiplayerPicture.getSize().x) / 2,
        (Game::windowHeight - buttonMultiplayerPicture.getSize().y) / 2 + 150
    );
}

void MainMenuScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<LevelMapScene>());
            return;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (buttonSingleplayer.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<LevelMapScene>());
                return;
            }
        }
    }
}

void MainMenuScene::update(sf::Time &dTime) {
}

void MainMenuScene::updateSceneSize() {
    // update positions of all objects
    bigRectangle.setPosition(
        (Game::windowWidth - bigRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - bigRectanglePicture.getSize().y) / 2 - 50
    );

    buttonSingleplayer.setPosition(
        (Game::windowWidth - buttonSingleplayerPicture.getSize().x) / 2,
        (Game::windowHeight - buttonSingleplayerPicture.getSize().y) / 2 + 50
    );

    buttonMultiplayer.setPosition(
        (Game::windowWidth - buttonMultiplayerPicture.getSize().x) / 2,
        (Game::windowHeight - buttonMultiplayerPicture.getSize().y) / 2 + 150
    );

}

void MainMenuScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(bigRectangle);
    window.draw(text);
    window.draw(buttonSingleplayer);
    window.draw(buttonMultiplayer);
    window.display();
}

}  // namespace super_hse
