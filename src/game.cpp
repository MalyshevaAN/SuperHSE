#include "game.hpp"
#include <iostream>
#include <memory>
#include "authentication_scene.hpp"
#include "scene.hpp"

namespace super_hse {

int Game::windowWidth = 1180;
int Game::windowHeight = 760;

int Game::defaultWindowWidth = 1180;
int Game::defaultWindowHeight = 760;

int Game::player_id = -1;
std::string Game::player_name = "NULL";
int Game::errorOn = false;

Game::Game()
    : window(sf::VideoMode(windowWidth, windowHeight, 32), "Super HSE"),
      sceneManager() {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    if (!music.openFromFile("../assets/audio/best_song.wav")) {
        std::cerr << "Error loading audio file best_song.wav" << '\n';
        return;
    }
    music.setVolume(50);
    music.play();
    music.setLoop(true);

    get_texture_from_file("sound_off.png", muteSoundButtonTexture);
    get_texture_from_file("sound_on.png", unmuteSoundButtonTexture);
    soundButton.setTexture(unmuteSoundButtonTexture);
    soundButton.setPosition(100, 20);

    // set icon
    const std::filesystem::path p = std::filesystem::current_path();
    const std::string texture_path =
        p.parent_path().string() + "/assets/images/logo2.png";
    if (!icon.loadFromFile(texture_path)) {
        std::cerr << "Error loading texture file logo2.png" << '\n';
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    get_texture_from_file("back_button.png", backButtonTexture);
    backButton.setTexture(backButtonTexture);
    backButton.setPosition(20, 20);
    backButton.setScale(0.8, 0.8);
}

void Game::run() {
    SceneManager::changeScene(std::make_unique<AuthenticationScene>());

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (window.hasFocus()) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::Resized) {
                    windowWidth = window.getSize().x;
                    windowHeight = window.getSize().y;

                    const sf::FloatRect visibleArea(
                        0, 0, event.size.width, event.size.height
                    );
                    window.setView(sf::View(visibleArea));

                    SceneManager::updateSceneSize();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left &&
                        soundButton.getGlobalBounds().contains(
                            event.mouseButton.x, event.mouseButton.y
                        )) {
                        isSoundOn = !isSoundOn;
                        if (isSoundOn) {
                            music.play();
                            soundButton.setTexture(unmuteSoundButtonTexture);
                        } else {
                            music.pause();
                            soundButton.setTexture(muteSoundButtonTexture);
                        }
                    }
                }

                SceneManager::handleInput(event);
            }
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
        window.create(
            sf::VideoMode(windowWidth, windowHeight, 32), "Super HSE",
            sf::Style::Default
        );

    } else {
        window.create(
            sf::VideoMode::getDesktopMode(), "Super HSE", sf::Style::Fullscreen
        );
        windowWidth = window.getSize().x;
        windowHeight = window.getSize().y;
    }
    SceneManager::updateSceneSize();
    isFullScreen = !isFullScreen;

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

}  // namespace super_hse
