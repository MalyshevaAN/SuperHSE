#ifndef WIN_SCENE_CPP
#define WIN_SCENE_CPP

#include "win_scene.hpp"
#include <memory>
#include <string>
#include "game.hpp"
#include "hse_utils.hpp"
#include "level_scene.hpp"
#include "main_menu_scene.hpp"
#include "sql.hpp"
#include "multi_connect_scene.hpp"

namespace super_hse {

WinScene::WinScene() {
}

WinScene::WinScene(int coins_, int level_numb_, int saved_lives_, char state_)
    : coins(coins_), level_numb(level_numb_), saved_lives(saved_lives_), state(state_){
    get_texture_from_file("win_scene.png", BackgroundTexture);
    get_texture_from_file("main_menu_button.png", MainMenuTexture);
    get_texture_from_file("try_again_button.png", TryAgainTexture);
    get_texture_from_file("next_level_button.png", NextLevelTexture);
    get_texture_from_file("HSEcoin.png", CoinTexture);
    get_texture_from_file("life.png", LivesTexture);
    get_texture_from_file("graduated.png", GraduateTexture);

    background.setTexture(BackgroundTexture);
    mainMenu.setTexture(MainMenuTexture);
    tryAgain.setTexture(TryAgainTexture);
    nextLevel.setTexture(NextLevelTexture);
    coin.setTexture(CoinTexture);
    lives.setTexture(LivesTexture);
    graduate.setTexture(GraduateTexture);
    coin.setTextureRect({0, 0, 16, 16});

    graduate.setOrigin(
        graduate.getTexture()->getSize().x / 2,
        graduate.getTexture()->getSize().x / 2
    );

    int drop = 0;
    if (level_numb == all_levels) {
        drop = 100;
    }

    background.setPosition(
        (Game::windowWidth - background.getTexture()->getSize().x) / 2,
        Game::windowHeight / 5.5
    );
    mainMenu.setPosition(
        (Game::windowWidth - mainMenu.getTexture()->getSize().x) / 2,
        Game::windowHeight / 2 + drop
    );
    tryAgain.setPosition(
        (Game::windowWidth - tryAgain.getTexture()->getSize().x) / 2,
        Game::windowHeight / 1.5 + drop
    );
    nextLevel.setPosition(
        (Game::windowWidth - nextLevel.getTexture()->getSize().x) / 2,
        Game::windowHeight / 1.2 + drop
    );
    coin.setPosition(
        (Game::windowWidth - coin.getTexture()->getSize().x) / 2.2 + 140,
        Game::windowHeight / 2.85
    );
    lives.setPosition(
        (Game::windowWidth - lives.getTexture()->getSize().x) / 1.8 + 140,
        Game::windowHeight / 2.85
    );
    graduate.setPosition(Game::windowWidth / 2, Game::windowHeight / 2);

    graduate.setScale(0.01, 0.01);
    coin.setScale(3, 3);
    lives.setScale(1.5, 1.5);

    if (!font.loadFromFile("../assets/fonts/8bit.ttf")) {
        std::cerr << "Error loading font\n";
    }
    collected_coins.setFont(font);
    collected_coins.setCharacterSize(30);
    collected_coins.setFillColor(sf::Color::Black);
    collected_coins.setPosition(
        (Game::windowWidth - coin.getTexture()->getSize().x) / 2.3 + 130,
        Game::windowHeight / 3
    );
    collected_coins.setString(std::to_string(coins_));
    saved_lives_count.setFont(font);
    saved_lives_count.setCharacterSize(30);
    saved_lives_count.setFillColor(sf::Color::Black);
    saved_lives_count.setPosition(
        (Game::windowWidth - lives.getTexture()->getSize().x) / 1.9 + 140,
        Game::windowHeight / 3
    );
    saved_lives_count.setString(std::to_string(saved_lives_));
    int number = state == 's' ? level_numb : 5;
    updateLevel(Game::player_id, number, saved_lives_, coins_);
    updateBalance(Game::player_id, getBalance(Game::player_id) + coins_);
    LvlRecords info = getLevelRecords(Game::player_id, level_numb_);

    records_txt.setFont(font);
    records_txt.setCharacterSize(30);
    records_txt.setFillColor(sf::Color::Black);
    records_txt.setPosition(
        (Game::windowWidth - coin.getTexture()->getSize().x) / 5 + 130,
        Game::windowHeight / 2.7
    );
    records_txt.setString("Best results:");
    result_txt.setFont(font);
    result_txt.setCharacterSize(30);
    result_txt.setFillColor(sf::Color::Black);
    result_txt.setPosition(
        (Game::windowWidth - coin.getTexture()->getSize().x) / 5 + 130,
        Game::windowHeight / 3
    );
    result_txt.setString("Your results:");
    best_coins.setFont(font);
    best_coins.setCharacterSize(30);
    best_coins.setFillColor(sf::Color::Black);
    best_coins.setPosition(
        (Game::windowWidth - coin.getTexture()->getSize().x) / 2.3 + 130,
        Game::windowHeight / 2.7
    );
    best_coins.setString(std::to_string(info.coins));
    best_lives.setFont(font);
    best_lives.setCharacterSize(30);
    best_lives.setFillColor(sf::Color::Black);
    best_lives.setPosition(
        (Game::windowWidth - lives.getTexture()->getSize().x) / 1.9 + 140,
        Game::windowHeight / 2.7
    );
    best_lives.setString(std::to_string(info.lives));
}

void WinScene::handleInput(sf::Event &event) {
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
            if (mainMenu.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
            if (tryAgain.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                if (state == 's'){
                    SceneManager::changeScene(
                        std::make_unique<LevelScene>(level_numb - 1)
                    );
                    return;
                }else if (state == 'm'){
                    SceneManager::changeScene(
                        std::make_unique<MultiConnectScene>()
                    );
                }
            }
            if (nextLevel.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                ) &&
                level_numb < all_levels) {
                SceneManager::changeScene(
                    std::make_unique<LevelScene>(level_numb)
                );
                return;
            }
        }
    }
}

void WinScene::update(sf::Time &dTime) {
    if (level_numb == all_levels) {
        if (graduate.getScale().x <= 0.3f) {
            graduate.setScale(
                graduate.getScale().x + 0.01f, graduate.getScale().y + 0.01f
            );
        }
    }
}

void WinScene::updateSceneSize() {
}

void WinScene::draw(sf::RenderWindow &window) {
    sf::View view;
    view.setSize(Game::windowWidth, Game::windowHeight);
    view.setCenter(Game::windowWidth / 2, Game::windowHeight / 2);
    window.clear(backgroundColor);
    window.setView(view);
    window.draw(background);
    window.draw(mainMenu);
    window.draw(tryAgain);
    if (level_numb < all_levels) {
        window.draw(nextLevel);
    }

    if (level_numb == all_levels) {
        window.draw(graduate);
    }
    window.draw(coin);
    window.draw(lives);
    window.draw(collected_coins);
    window.draw(saved_lives_count);
    window.draw(result_txt);
    window.draw(records_txt);
    window.draw(best_coins);
    window.draw(best_lives);
    window.display();
}
} 

#endif
