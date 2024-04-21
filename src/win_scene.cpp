#ifndef WIN_SCENE_CPP
#define WIN_SCENE_CPP

#include "win_scene.hpp"
#include "hse_utils.hpp"
#include <memory>
#include "game.hpp"
#include "main_menu_scene.hpp"
#include "level_scene.hpp"
#include <string>

namespace super_hse{

WinScene::WinScene(){
    
}

WinScene::WinScene(int coins_, int level_numb_, int saved_lives_) : coins(coins_), level_numb(level_numb_), saved_lives(saved_lives_){
    get_texture_from_file("win_scene.png", BackgroundTexture);
    get_texture_from_file("main_menu_button.png", MainMenuTexture);
    get_texture_from_file("try_again_button.png", TryAgainTexture);
    get_texture_from_file("next_level_button.png", NextLevelTexture);
    get_texture_from_file("HSEcoin.png", CoinTexture);
    get_texture_from_file("live.png", LivesTexture);

    background.setTexture(BackgroundTexture);
    mainMenu.setTexture(MainMenuTexture);
    tryAgain.setTexture(TryAgainTexture);
    nextLevel.setTexture(NextLevelTexture);
    coin.setTexture(CoinTexture);
    lives.setTexture(LivesTexture);
    coin.setTextureRect({0,0,16,16});

    mainMenu.setPosition((Game::windowWidth - mainMenu.getTexture()->getSize().x)/2, Game::windowHeight / 2);
    tryAgain.setPosition((Game::windowWidth - tryAgain.getTexture()->getSize().x)/2, Game::windowHeight / 1.5);
    nextLevel.setPosition((Game::windowWidth - nextLevel.getTexture()->getSize().x)/2, Game::windowHeight / 1.2);
    coin.setPosition((Game::windowWidth - coin.getTexture()->getSize().x)/2.2, Game::windowHeight / 3);
    lives.setPosition((Game::windowWidth - lives.getTexture()->getSize().x)/1.8, Game::windowHeight / 3);

    coin.setScale(3, 3);
    lives.setScale(1.5, 1.5);

    if (!font.loadFromFile("../assets/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
    }
    gathered_coins.setFont(font);
    gathered_coins.setCharacterSize(30);
    gathered_coins.setFillColor(sf::Color::Black);
    gathered_coins.setPosition((Game::windowWidth - coin.getTexture()->getSize().x)/2.3, Game::windowHeight / 3);
    gathered_coins.setString(std::to_string(coins_));
    saved_lives_count.setFont(font);
    saved_lives_count.setCharacterSize(30);
    saved_lives_count.setFillColor(sf::Color::Black);
    saved_lives_count.setPosition((Game::windowWidth - lives.getTexture()->getSize().x)/1.9, Game::windowHeight / 3);
    saved_lives_count.setString(std::to_string(saved_lives_));

    // тут очень надо подрубаться к бд, чтобы сохранять результат по новому уровню и открывать в доступ следующий уровень 
}

void WinScene::handleInput(sf::Event &event){
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
            if (mainMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
            // не работает почему-то ((
            if (tryAgain.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                SceneManager::changeScene(std::make_unique<LevelScene>(level_numb - 1));
                return;
            }
            if (nextLevel.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && level_numb < all_levels){
                SceneManager::changeScene(std::make_unique<LevelScene>(level_numb));
                return;
            }
        }
    }
}

void WinScene::update(sf::Time &dTime){

}

void WinScene::updateSceneSize(){

}

void WinScene::draw(sf::RenderWindow &window){
    sf::View view;
    view.setSize(Game::windowWidth, Game::windowHeight);
    view.setCenter(Game::windowWidth / 2, Game::windowHeight / 2);
    window.clear(backgroundColor);
    window.setView(view);
    window.draw(background);
    window.draw(mainMenu);
    window.draw(tryAgain);
    if (level_numb < all_levels){
        window.draw(nextLevel);
    }
    window.draw(coin);
    window.draw(lives);
    window.draw(gathered_coins);
    window.draw(saved_lives_count);
    window.display();
}
}

#endif
