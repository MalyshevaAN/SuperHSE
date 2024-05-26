#include "level_scene.hpp"
#include <LDtkLoader/Project.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "Level.hpp"
#include "TileMap.hpp"
#include "game.hpp"
#include "level_map_scene.hpp"
#include "lose_scene.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"
#include "sql.hpp"

namespace super_hse {

LevelScene::LevelScene(int levelN) {
    get_texture_from_file("pause_button.png", pauseButtonPicture);
    pauseButton.setTexture(pauseButtonPicture);

    levelNumber = levelN;

    std::string filename = storage.storage.at(levelNumber)->filename;
    level.ldtk_filename = storage.storage.at(levelNumber)->filename;
    level.project.loadFromFile(filename);
    level.init(
        storage.storage.at(levelNumber)->tileLayerName,
        storage.storage.at(levelNumber)->entityLayerName,
        storage.storage.at(levelNumber)->colliderName, levelN
    );
    updateSceneSize();
}

void LevelScene::handleInput(sf::Event &event) {
    if (pauseState.isPaused) {
        pauseState.handleInput(event);
        return;
    } else if (loseState.isLose) {
        loseState.handleInput(event);
        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            pauseState.isPaused = !pauseState.isPaused;
            return;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (pauseButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                pauseState.isPaused = !pauseState.isPaused;
                return;
            }
        }
    }
    // player.handleInput(event);
}

void LevelScene::updateSceneSize() {
    pauseState.updateSceneSize();

    pauseButton.setPosition(20, 20);
    Game::soundButton.setPosition(
        pauseButton.getPosition().x + pauseButtonPicture.getSize().x + 20,
        20
    );
}

void LevelScene::update(sf::Time &dTime) {
    if (pauseState.isPaused) {
        pauseState.update(dTime);
        return;
    } else if (loseState.isLose) {
        loseState.update(dTime);
        return;
    }
    
    if (player.get_active_lives() == 0) {
        loseState.isLose = true;
        loseState.timer.restart();
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

    for (auto &coin : level.coins) {
        if (nextPositionCollider.intersects(coin.coin_sprite.getGlobalBounds()
            )) {
            coin.disable();
        }
    }

    for (auto &enemy : level.enemies) {
        if (nextPositionCollider.intersects(enemy.enemySprite.getGlobalBounds()
            ) && enemy.get_state() == EnemyState::active) {
            if (nextPositionCollider.top + nextPositionCollider.height - 4 <=
                    enemy.enemySprite.getPosition().y &&
                movement.y > 0) {
                enemy.disable();
            } else {
                if (enemy.get_state() == EnemyState::active) {
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

    sf::View fullWindowView(
        sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)
    );
    window.setView(fullWindowView);
    window.draw(Game::soundButton);
    window.draw(pauseButton);

    if (pauseState.isPaused) {
        pauseState.draw(window);
    } else if (loseState.isLose) {
        loseState.draw(window);
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

LoseState::LoseState() {
    // у стейта паузы такой же фон, возьмем его
    get_texture_from_file("pause.png", loseRectanglePicture);
    loseRectangle.setTexture(loseRectanglePicture);

    get_texture_from_file("pay_resume_button.png", payResumeButtonPicture);
    payResumeButton.setTexture(payResumeButtonPicture);
    
    get_texture_from_file("HSEcoin.png", coinTexture);
    coin.setTexture(coinTexture);
    coin.setTextureRect({0, 0, 16, 16});
    coin.setScale(3, 3);

    if (!font.loadFromFile("../assets/fonts/Karma.ttf")) {
        std::cerr << "Error loading font\n";
    }
    if (!font_8bit.loadFromFile("../assets/fonts/8bit.ttf")) {
        std::cerr << "Error loading font\n";
    }
    balance.setFont(font);
    balance.setCharacterSize(30);
    balance.setFillColor(sf::Color::Black);
    balance.setString(std::to_string(getBalance(Game::player_id)));

    timerText.setFont(font_8bit);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::Black);
    timerText.setString("Time left: " + std::to_string(loseStateTime));
    
    updateSceneSize();
}

void LoseState::update(sf::Time &dTime) {
    const int timeLeft = loseStateTime - timer.getElapsedTime().asSeconds();
    timerText.setString("Time left: " + std::to_string(timeLeft));

    if (timer.getElapsedTime().asSeconds() >= loseStateTime) {
        super_hse::SceneManager::changeScene(std::make_unique<super_hse::LoseScene>());
    }
}

void LoseState::draw(sf::RenderWindow &window) {
    window.draw(loseRectangle);
    window.draw(payResumeButton);
    window.draw(coin);
    window.draw(balance);
    window.draw(timerText);
}

void LoseState::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (payResumeButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                // TODO норм возвращение в игру

                int resumeCost = 5;
                bool success = buyResume(Game::player_id, resumeCost);
                if (success) {
                //     SceneManager::changeScene(std::make_unique<LevelScene>(0));
                    isLose = false;
                    return;
                } else {
                    std::cerr << "Oops... Go and earn more HSEcoins!\n";
                }
                return;
            }
        }
    }
}

void LoseState::updateSceneSize() {
    loseRectangle.setPosition(
        (Game::windowWidth - loseRectanglePicture.getSize().x) / 2,
        (Game::windowHeight - loseRectanglePicture.getSize().y) / 2
    );
    payResumeButton.setPosition(
        (Game::windowWidth - payResumeButtonPicture.getSize().x) / 2,
        (Game::windowHeight - payResumeButtonPicture.getSize().y) / 2
    );
    coin.setPosition(
        (Game::windowWidth - coinTexture.getSize().x) / 2 - 20,
        (Game::windowHeight - coinTexture.getSize().y) / 2 - 100
    );
    balance.setPosition(
        coin.getPosition().x + coinTexture.getSize().x + 10,
        coin.getPosition().y
    );
    timerText.setPosition(
        (Game::windowWidth - timerText.getGlobalBounds().width) / 2,
        (Game::windowHeight - timerText.getGlobalBounds().height) / 2 + 100
    );
}


}  // namespace super_hse
