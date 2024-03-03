#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <filesystem>
#include <memory>
#include <random>
#include "scene.hpp"

namespace super_hse {

class Game {
private:
    sf::RenderWindow window;
    SceneManager sceneManager;

public:
    static int windowWidth;
    static int windowHeight;

    Game()
        : window(sf::VideoMode(windowWidth, windowHeight, 32), "SFML Window"),
          sceneManager(){};
    void run();
};

}  // namespace super_hse
#endif  // GAME_HPP_
