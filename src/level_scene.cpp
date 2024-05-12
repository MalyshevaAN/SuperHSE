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
    level.ldtk_filename = storage.storage.at(levelNumber)->filename;
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
        }
    }
    // player.handleInput(event);
}

void LevelScene::updateSceneSize() {
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
    // посчитаем следующую возможную позицию игрока
    sf::FloatRect nextPositionCollider = player.getCollider();
    sf::Vector2f movement = player.calcMovement(dTime);
    nextPositionCollider.left += movement.x;
    nextPositionCollider.top += movement.y;

    // Проверяем, будет ли пересечение с блоками
    const float dTimeSeconds = dTime.asSeconds();

    bool isCollidingWithWall = false;
    bool isCollidingWithFloor = false;
    for (auto &entity : level.colliders) {
        sf::FloatRect intersect;
        if (nextPositionCollider.intersects(entity, intersect)) {
            // проверить тип объекта, с кем пересеклись (в данном случае -
            // стены/пол)
            // TODO - добавить проверку на тип объекта (тут нужна Настя и её
            // енамы)

            // проверка что пересекаемся с полом
            if (nextPositionCollider.top + nextPositionCollider.height >=
                entity.top) {
                isCollidingWithFloor = true;
                nextPositionCollider.top -= movement.y;
                movement.y = 0;

                // если после отката человечка наверх мы всё равно пересекаемся
                // с блоком - значит он стена
                if (nextPositionCollider.intersects(entity, intersect)) {
                    isCollidingWithWall = true;
                }
            } else {
                isCollidingWithWall = true;
            }
        }
    }

    for (auto &coin : level.coins){
        if (nextPositionCollider.intersects(coin.coin_sprite.getGlobalBounds())){
            coin.disable();
        }
    }

    for (auto &enemy : level.enemies){
        if (nextPositionCollider.intersects(enemy.enemySprite.getGlobalBounds()) && enemy.get_state() == EnemyState::active){
            if (nextPositionCollider.top + nextPositionCollider.height - 4 <= enemy.enemySprite.getPosition().y && movement.y > 0){
                enemy.disable();
            }else{
                if (enemy.get_state() == EnemyState::active){
                    player.lose_life();
                }
                enemy.unable();
            }
        }
    }

    player.isGrounded = isCollidingWithFloor;

    if (!isCollidingWithWall) {
        player.move(movement.x, 0);
    }
    if (!isCollidingWithFloor) {
        player.move(0, movement.y);
    }

    // обновление фрейма
    player.update(dTime);
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
