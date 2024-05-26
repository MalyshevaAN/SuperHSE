#include "level_map_scene.hpp"
#include <filesystem>
#include <memory>
#include "game.hpp"
#include "hse_utils.hpp"
#include "level_icon.hpp"
#include "level_scene.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"

namespace super_hse {

LevelMapScene::LevelMapScene() {
    get_texture_from_file("level_map.png", levelMapTexture);
    levelMap.setTexture(levelMapTexture);
    levelIcons.resize(4);
    for (int i = 0; i < 4; ++i) {
        levelIcons[i] = levelIcon(i + 1);
    }
    get_texture_from_file("clothes.png", clothesTexture);
    clothes.setTexture(clothesTexture);
}

void LevelMapScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            SceneManager::changeScene(std::make_unique<LevelScene>(0));
            return;
        } else if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (Game::backButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
            for (const auto &elem : levelIcons) {
                if (elem.levelIconSprite.getGlobalBounds().contains(
                        event.mouseButton.x, event.mouseButton.y
                    ) &&
                    elem.available) {
                    SceneManager::changeScene(
                        std::make_unique<LevelScene>(elem.number - 1)
                    );
                    return;
                }
            }
        }
    }
}

void LevelMapScene::update(sf::Time &dTime) {
}

void LevelMapScene::updateSceneSize() {
}

void LevelMapScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    double x_scale =
        Game::windowWidth / static_cast<double>(Game::defaultWindowWidth);
    double y_scale =
        Game::windowHeight / static_cast<double>(Game::defaultWindowHeight);
    levelMap.setScale(x_scale, y_scale);
    levelMap.setPosition(
        (Game::windowWidth - levelMap.getPosition().x) / 8,
        (Game::windowHeight - levelMap.getPosition().y) / 8
    );
    window.draw(levelMap);
    for (auto &elem : levelIcons) {
        if (elem.available) {
            elem.levelIconSprite.setTexture(elem.levelIconTextureAvailable);
        } else {
            elem.levelIconSprite.setTexture(elem.levelIconTextureUnavailable);
        }
        int x = (Game::windowWidth - elem.levelIconTextureAvailable.getSize().x
                ) / 2 +
                (elem.number - 2.5) * (Game::windowWidth / 8);
        int y = (Game::windowHeight - elem.levelIconTextureAvailable.getSize().y
                ) / 2 +
                Game::windowHeight / 4;
        elem.levelIconSprite.setPosition(x, y);
        elem.levelIconSprite.setScale(0.8, 0.8);
        window.draw(elem.levelIconSprite);
    }
    clothes.setPosition(
        (Game::windowWidth - clothesTexture.getSize().x) / 2 -
            Game::windowWidth / 6,
        (Game::windowHeight - clothesTexture.getSize().y) / 2 -
            Game::windowHeight / 7
    );
    clothes.setScale(x_scale, y_scale);
    window.draw(Game::backButton);
    window.draw(clothes);
    window.display();
}

}  // namespace super_hse
