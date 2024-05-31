#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <filesystem>
#include <memory>
#include <random>
#include <string>
#include "hse_utils.hpp"
#include "scene.hpp"

namespace super_hse {

class Game {
private:
    sf::RenderWindow window;
    SceneManager sceneManager;
    bool isFullScreen = false;
    sf::Image icon;

    bool isSoundOn = true;
    sf::Music music;

public:
    static int windowWidth;
    static int windowHeight;

    static int defaultWindowWidth;
    static int defaultWindowHeight;

    static inline sf::Sprite backButton;
    static inline sf::Texture backButtonTexture;

    static inline sf::Texture muteSoundButtonTexture;
    static inline sf::Texture unmuteSoundButtonTexture;
    static inline sf::Sprite soundButton;

    static int player_id;
    static std::string player_name;
    static int errorOn;

    const static int levelsCount = 4;
    const static int skinsCount = 8;

    Game();
    void run();

    void changeFullScreenMode();
};

}  // namespace super_hse
#endif  // GAME_HPP_
