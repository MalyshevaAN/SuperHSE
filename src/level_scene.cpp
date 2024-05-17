#include "level_scene.hpp"
#include <LDtkLoader/Project.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "Level.hpp"
#include "TileMap.hpp"
#include "level_map_scene.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"
#include "game.hpp"
#include "lose_scene.hpp"

namespace super_hse {

LevelScene::LevelScene(int levelN) {
    levelNumber = levelN;
    std::string filename = storage.storage.at(levelNumber)->filename;
    level.ldtk_filename = filename;
    level.project.loadFromFile(filename);
    level.init(
        storage.storage.at(levelNumber)->tileLayerName,
        storage.storage.at(levelNumber)->entityLayerName,
        storage.storage.at(levelNumber)->colliderName,
        levelN
    );
}

void LevelScene::handleInput(sf::Event &event) {
    if (pauseState.isPaused) {
        pauseState.handleInput(event);
        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            pauseState.isPaused = !pauseState.isPaused;
            return;
        }else if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }
    // player.handleInput(event);
}

void LevelScene::updateSceneSize() {
    pauseState.updateSceneSize();
}

void LevelScene::update(sf::Time &dTime) {
    if (pauseState.isPaused) {
        pauseState.update(dTime);
        return;
    }

    if (player.get_active_lives() == 0){
        SceneManager::changeScene(std::make_unique<LoseScene>());
        std::cerr << 1;
        return;
    }
    level.update(dTime, player.get_position(), player.get_active_lives());
    player.update(dTime);
    // посчитаем следующую возможную позицию игрока
    sf::FloatRect nextPositionCollider = player.getCollider();
    sf::Vector2f movement = player.calcMovement(dTime);
    nextPositionCollider.left += movement.x;
    nextPositionCollider.top += movement.y;
    // Проверяем, будет ли пересечение с блоками
    const float dTimeSeconds = dTime.asSeconds();
    answer answer_ = level.entities.update(nextPositionCollider, movement);
    if (answer_.lose_life){
        player.lose_life();
    }
    if(answer_.isCollidingWithFloor){
        movement.y = 0;
    }
    player.isGrounded = answer_.isCollidingWithFloor;
    if(!answer_.isCollidingWithWall){
        player.move(movement.x, 0);
    }
    if(!answer_.isCollidingWithFloor){
        player.move(0, movement.y);
    }

    // обновление фрейма
}

void LevelScene::draw(sf::RenderWindow &window) {
    window.clear(windowFillColor);
    level.render(window, storage.storage.at(levelNumber)->tileLayerName);
    player.draw(window);

    if (pauseState.isPaused) {
        sf::View fullWindowView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        window.setView(fullWindowView);
        pauseState.draw(window);
    }

    window.display();
}

PauseState::PauseState() {
    get_texture_from_file("pause.png", pauseRectanglePicture);
    pauseRectangle.setTexture(pauseRectanglePicture);

    get_texture_from_file("resume_button.png", resumeButtonPicture);
    resumeButton.setTexture(resumeButtonPicture);

    get_texture_from_file("level_map_button.png", levelMapButtonPicture);
    levelMapButton.setTexture(levelMapButtonPicture);

    get_texture_from_file("main_menu_button.png", mainMenuButtonPicture);
    mainMenuButton.setTexture(mainMenuButtonPicture);

    updateSceneSize();
}

void PauseState::update(sf::Time &dTime) {
}

void PauseState::draw(sf::RenderWindow &window) {
    window.draw(pauseRectangle);
    window.draw(resumeButton);
    window.draw(levelMapButton);
    window.draw(mainMenuButton);
}

void PauseState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (resumeButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                isPaused = false;
                return;
            }
            if (levelMapButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<LevelMapScene>());
                return;
            }
            if (mainMenuButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
        }
    }
}

void PauseState::updateSceneSize() {
    pauseRectangle.setPosition(
        (Game::windowWidth - pauseRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - pauseRectanglePicture.getSize().y) / 2
    );
    resumeButton.setPosition(
        (Game::windowWidth - resumeButtonPicture.getSize().x) / 2,
        (Game::windowHeight - resumeButtonPicture.getSize().y) / 2 - 100
    );
    levelMapButton.setPosition(
        (Game::windowWidth - levelMapButtonPicture.getSize().x) / 2,
        (Game::windowHeight - levelMapButtonPicture.getSize().y) / 2
    );
    mainMenuButton.setPosition(
        (Game::windowWidth - mainMenuButtonPicture.getSize().x) / 2,
        (Game::windowHeight - mainMenuButtonPicture.getSize().y) / 2 + 100
    );
}

} // namespace super_hse
