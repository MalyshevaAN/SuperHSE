#include <memory>
#include "scene.hpp"
#include "level_map_scene.hpp"
#include "game.hpp"

namespace super_hse {

MainMenuScene::MainMenuScene() {
    // возможно потом лучше разбить конструктор на несколько отдельных функций

    // bigRectangle init
    if (!bigRectanglePicture.loadFromFile("../assets/images/main_menu_scene_big_rectangle.png")) {
        std::cerr << "Error loading main_menu_scene_big_rectangle.png\n";
    }
    bigRectanglePicture.setSmooth(true);
    bigRectangle.setTexture(bigRectanglePicture);
    // скаляр временный, пока нет нормальных картинок для уровня
    float scale = 1.6;
    bigRectangle.setScale(scale, scale);
    bigRectangle.setPosition(
        (Game::windowWidth - bigRectanglePicture.getSize().x * scale) / 2,
        (Game::windowHeight - bigRectanglePicture.getSize().y * scale) / 2
    );
    
    // buttons init
    float buttonWidthScale = 0.6;
    float buttonHeightScale = 0.2;

    if (!buttonSingleplayerPicture.loadFromFile("../assets/images/main_menu_scene_button_singleplayer.png")) {
        std::cerr << "Error loading main_menu_scene_button_singleplayer.png\n";
    }
    buttonSingleplayerPicture.setSmooth(true);
    buttonSingleplayer.setTexture(buttonSingleplayerPicture);
    buttonSingleplayer.setScale(buttonWidthScale, buttonHeightScale);
    buttonSingleplayer.setPosition(
        (Game::windowWidth - buttonSingleplayerPicture.getSize().x * buttonWidthScale) / 2,
        (Game::windowHeight - buttonSingleplayerPicture.getSize().y * buttonHeightScale) / 2
    );

    if (!buttonMultiplayerPicture.loadFromFile("../assets/images/main_menu_scene_button_multiplayer.png")) {
        std::cerr << "Error loading main_menu_scene_option_button.png\n";
    }
    buttonMultiplayerPicture.setSmooth(true);
    buttonMultiplayer.setTexture(buttonMultiplayerPicture);
    buttonMultiplayer.setScale(buttonWidthScale, buttonHeightScale);
    buttonMultiplayer.setPosition(
        (Game::windowWidth - buttonMultiplayerPicture.getSize().x * buttonWidthScale) / 2,
        (Game::windowHeight - buttonMultiplayerPicture.getSize().y * buttonHeightScale) / 2 + 100
    );

    // text init
    if (!font.loadFromFile("../assets/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
    }
    text.setFont(font);
    text.setString("This is the main menu. \nPress M (or click on button with your mouse) to go to the level map!");
    text.setCharacterSize(24); 
    text.setFillColor(sf::Color::Black);
    text.setPosition(150, 10);
}

void MainMenuScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<LevelMapScene>());
            return;
        }
    }
    // тык на кнопку "singleplayer"
    // пока что тут просто переход на карту уровня
    // TODO проверить что игрок залогинился(?) и только после этого разрешать ему переход на карту и в целом игру
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (buttonSingleplayer.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                SceneManager::changeScene(std::make_unique<LevelMapScene>());
                return;
            }
        }
    }
}

void MainMenuScene::update(sf::Time &dTime) {

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
