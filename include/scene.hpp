#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <random>

namespace super_hse {

enum class SceneType {
    MAIN_MENU,
    LEVEL_MAP,
    NONE
};

class Scene {
public:
    Scene() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void handleInput(sf::RenderWindow &window) = 0;
};

class LevelMapScene : public Scene {
private:
    sf::Texture levelMapPicture;
    sf::Sprite label;

public:
    LevelMapScene();
    void update() override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::RenderWindow &window) override;
};

class MainMenuScene : public Scene {
private:
    sf::Texture mainMenuLabel;
    sf::Sprite label;

public:
    MainMenuScene();

    void update() override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::RenderWindow &window) override;
};

class SceneManager {
private:
    std::unique_ptr<Scene> currentScene;
public:
    static bool needToChangeScene;
    static SceneType nextSceneType;

    void handleInput(sf::RenderWindow& window);
    void changeScene(std::unique_ptr<Scene> newScene);
    void update();
    void draw(sf::RenderWindow &window);
};

} // namespace super_hse

#endif // SCENE_HPP_
