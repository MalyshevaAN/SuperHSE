#ifndef LOSE_SCENE_CPP
#define LOSE_SCENE_CPP

#include "hse_utils.hpp"
#include <memory>
#include "lose_scene.hpp"
#include "game.hpp"
#include "main_menu_scene.hpp"
#include "level_scene.hpp"
namespace super_hse{

LoseScene::LoseScene(){
    get_texture_from_file("lose_scene.png", BackGroundTexture);
    get_texture_from_file("main_menu_button.png", MainMenuTexture);
    get_texture_from_file("try_again_button.png", TryAgainTexture);
    background.setTexture(BackGroundTexture);
    mainMenu.setTexture(MainMenuTexture);
    tryAgain.setTexture(TryAgainTexture);
    mainMenu.setPosition((Game::windowWidth - mainMenu.getTexture()->getSize().x)/2, Game::windowHeight / 2);
    tryAgain.setPosition((Game::windowWidth - tryAgain.getTexture()->getSize().x)/2, Game::windowHeight / 1.5);
}

void LoseScene::handleInput(sf::Event &event){
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
                SceneManager::changeScene(std::make_unique<LevelScene>(0));
                return;
            }
        }
    }

}

void LoseScene::update(sf::Time &dTime){

}

void LoseScene::updateSceneSize(){

}

void LoseScene::draw(sf::RenderWindow &window){
    sf::View view;
    view.setCenter(Game::windowWidth / 2, Game::windowHeight / 2);
    window.clear(backgroundColor);
    window.setView(view);
    window.draw(background);
    window.draw(mainMenu);
    window.draw(tryAgain);
    window.display();
}
}

#endif
