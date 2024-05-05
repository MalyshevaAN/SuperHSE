#include "wardrobe_scene.hpp"
#include <filesystem>
#include <memory>
#include "game.hpp"
#include "hse_utils.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"
#include "sql.hpp"

namespace super_hse {

WardrobeScene::WardrobeScene() {
    get_texture_from_file("skin1.png", skin1Texture);
    skin1.setTexture(skin1Texture);
    get_texture_from_file("skin2.png", skin2Texture);
    skin2.setTexture(skin2Texture);
    get_texture_from_file("skin3.png", skin3Texture);
    skin3.setTexture(skin3Texture);
    get_texture_from_file("skin4.png", skin4Texture);
    skin4.setTexture(skin4Texture);
    get_texture_from_file("skin5.png", skin5Texture);
    skin5.setTexture(skin5Texture);
    get_texture_from_file("skin6.png", skin6Texture);
    skin6.setTexture(skin6Texture);

    updateSceneSize();
}

void WardrobeScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (skin1.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                updateSkin(Game::player_id, 1);
            }
            if (skin2.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                updateSkin(Game::player_id, 2);
            }
            if (skin3.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                updateSkin(Game::player_id, 3);
            }
            if (skin4.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                updateSkin(Game::player_id, 4);
            }
            if (skin5.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                updateSkin(Game::player_id, 5);
            }
            if (skin6.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                updateSkin(Game::player_id, 6);
            }
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }
}

void WardrobeScene::update(sf::Time &dTime) {
}

void WardrobeScene::updateSceneSize() {
    float buttonWidth = 126.0f;
    float buttonHeight = 126.0f;
    float distanceBetweenButtons = (Game::windowWidth - 3 * buttonWidth) / 4;

    skin1.setPosition(distanceBetweenButtons, (Game::windowHeight - 2 * buttonHeight) / 3);
    skin2.setPosition(2 * distanceBetweenButtons + buttonWidth, (Game::windowHeight - 2 * buttonHeight) / 3);
    skin3.setPosition(3 * distanceBetweenButtons + 2 * buttonWidth, (Game::windowHeight - 2 * buttonHeight) / 3);
    skin4.setPosition(distanceBetweenButtons, 2 * (Game::windowHeight - 2 * buttonHeight) / 3 + buttonHeight);
    skin5.setPosition(2 * distanceBetweenButtons + buttonWidth, 2 * (Game::windowHeight - 2 * buttonHeight) / 3 + buttonHeight);
    skin6.setPosition(3 * distanceBetweenButtons + 2 * buttonWidth, 2 * (Game::windowHeight - 2 * buttonHeight) / 3 + buttonHeight);
}

void WardrobeScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(skin1);
    window.draw(skin2);
    window.draw(skin3);
    window.draw(skin4);
    window.draw(skin5);
    window.draw(skin6);

    window.draw(Game::backButton);
    window.display();
}

}  // namespace super_hse
