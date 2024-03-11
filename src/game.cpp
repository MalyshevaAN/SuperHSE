#include "game.hpp"
#include <memory>
#include "scene.hpp"
#include "main_menu_scene.hpp"


#include <iostream>

namespace super_hse {

int Game::windowWidth = 960;
int Game::windowHeight = 640;

int Game::defaultWindowWidth = 960;
int Game::defaultWindowHeight = 640;

Game::Game()
    : window(sf::VideoMode(windowWidth, windowHeight, 32), "Super HSE"), sceneManager() {
        window.setFramerateLimit(60);
        window.setVerticalSyncEnabled(true);

        // set icon
        std::filesystem::path p = std::filesystem::current_path();
        std::string texture_path = p.parent_path().string() + "/assets/images/logo2.png";

        if (!icon.loadFromFile(texture_path)){
            std::cerr << "Error loading texture file logo2.png" << '\n';
        }
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

void Game::run() {
    SceneManager::changeScene(std::make_unique<MainMenuScene>());

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                windowWidth = window.getSize().x;
                windowHeight = window.getSize().y;

                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                SceneManager::updateSceneSize();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                changeFullScreenMode();
            }
            
            SceneManager::handleInput(event);
        }

        sf::Time dTime = clock.restart();
        SceneManager::update(dTime);
        SceneManager::draw(window);
    }
}
void Game::changeFullScreenMode() {
    window.close();

    if (isFullScreen) {
        windowWidth = defaultWindowWidth;
        windowHeight = defaultWindowHeight;
        window.create(sf::VideoMode(windowWidth, windowHeight, 32), "Super HSE", sf::Style::Default);

    } else {
        window.create(sf::VideoMode::getDesktopMode(), "Super HSE", sf::Style::Fullscreen);
        windowWidth = window.getSize().x;
        windowHeight = window.getSize().y;
    }
    SceneManager::updateSceneSize();
    isFullScreen = !isFullScreen;

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

}  // namespace super_hse