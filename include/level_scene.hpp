#ifndef LEVEL_SCENE_HPP_
#define LEVEL_SCENE_HPP_

#include "scene.hpp"
#include "level_info.hpp"

namespace super_hse {

struct PauseState {
private:
    sf::Texture pauseRectanglePicture;
    sf::Sprite pauseRectangle;

    sf::Texture resumeButtonPicture;
    sf::Sprite resumeButton;

    sf::Texture levelMapButtonPicture;
    sf::Sprite levelMapButton;

    sf::Texture mainMenuButtonPicture;
    sf::Sprite mainMenuButton;

public:
    PauseState();

    bool isPaused = false;

    void update(sf::Time &dTime);
    void updateSceneSize();
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event &event);
};

struct LoseState {
private:
    sf::Texture loseRectanglePicture;
    sf::Sprite loseRectangle;

    sf::Texture payResumeButtonPicture;
    sf::Sprite payResumeButton;

    sf::Font font;
    sf::Font font_8bit;
    sf::Text balance;
    sf::Texture coinTexture;
    sf::Sprite coin;

    const int resumeCost = 3;

    const float loseStateTime = 6;
    sf::Text timerText;

public:
    LoseState();
    bool isLose = false;
    bool isPaid = false;
    sf::Clock timer;

    void update(sf::Time &dTime);
    void updateSceneSize();
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event &event);
};

class LevelScene : public Scene {
private:
    std::string ldtk_filename;
    Player player;
    LevelsStorage storage;
    int levelNumber;
    Level level; 

    PauseState pauseState;
    sf::Texture pauseButtonPicture;
    sf::Sprite pauseButton;

    LoseState loseState;

    const sf::Color windowFillColor = sf::Color(125, 166, 218);

public:
    LevelScene() = default;
    LevelScene(int levelN);
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // LEVEL_SCENE_HPP_
