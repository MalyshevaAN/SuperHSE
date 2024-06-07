#ifndef LOSE_SCENE_CPP
#define LOSE_SCENE_CPP

#include "lose_scene.hpp"
#include <memory>
#include "game.hpp"
#include "hse_utils.hpp"
#include "level_scene.hpp"
#include "main_menu_scene.hpp"
#include "multi_connect_scene.hpp"

namespace super_hse {

LoseScene::LoseScene(char state_, int level_number_) : state(state_), level_number(level_number_) {
    get_texture_from_file("lose_scene.png", backgroundTexture);
    get_texture_from_file("main_menu_button.png", mainMenuTexture);
    get_texture_from_file("try_again_button.png", tryAgainTexture);
    get_texture_from_file("pay_resume_button.png", payResumeTexture);

    background.setTexture(backgroundTexture);
    mainMenu.setTexture(mainMenuTexture);
    tryAgain.setTexture(tryAgainTexture);
    payResume.setTexture(payResumeTexture);
    updateSceneSize();
}

void LoseScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (mainMenu.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
            // не работает почему-то ((
            if (tryAgain.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                if (state == 's'){
                    SceneManager::changeScene(std::make_unique<LevelScene>(level_number));
                    return;
                }else if(state == 'm'){
                    SceneManager::changeScene(std::make_unique<MultiConnectScene>());
                }
            }
            if (payResume.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
            }
        }
    }
}

void LoseScene::update(sf::Time &dTime) {
}

void LoseScene::updateSceneSize() {
    mainMenu.setPosition(
        (Game::windowWidth - mainMenu.getTexture()->getSize().x) / 2,
        Game::windowHeight / 2
    );
    tryAgain.setPosition(
        (Game::windowWidth - tryAgain.getTexture()->getSize().x) / 2,
        Game::windowHeight / 1.5
    );
    background.setPosition(
        (Game::windowWidth - background.getTexture()->getSize().x) / 2,
        Game::windowHeight / 4
    );
}

void LoseScene::draw(sf::RenderWindow &window) {
    sf::View view;
    view.setSize(Game::windowWidth, Game::windowHeight);
    view.setCenter(Game::windowWidth / 2, Game::windowHeight / 2);
    window.clear(backgroundColor);
    window.setView(view);
    window.draw(background);
    window.draw(mainMenu);
    window.draw(tryAgain);
    window.display();
}
}  // namespace super_hse

#endif
