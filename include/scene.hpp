#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <random>
#include "Level.hpp"
#include "player.hpp"

namespace super_hse {

enum class SceneType { MAIN_MENU, LEVEL_MAP, NONE };

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    Scene(Scene &&) = delete;
    Scene &operator=(Scene &&) = delete;

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void handleInput(sf::Event &event) = 0;
};

class SceneManager {
private:
    // NOLINTNEXTLINE [cppcoreguidelines-avoid-non-const-global-variables]
    static std::unique_ptr<Scene> currentScene;

public:
    static void changeScene(std::unique_ptr<Scene> newScene);

    static void handleInput(sf::Event &event);
    static void update();
    static void draw(sf::RenderWindow &window);
};

class MainMenuScene : public Scene {
private:
    sf::Texture mainMenuLabel;
    sf::Sprite label;

public:
    MainMenuScene();

    void update() override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
};

class LevelMapScene : public Scene {
private:
    sf::Texture levelMapPicture;
    sf::Sprite label;

public:
    LevelMapScene();
    void update() override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
};

class LevelScene : public Scene {
private:
    std::string ldtk_filename;
    Player player;
    LevelsStorage storage;
    int levelNumber;
    Level level;  // добавила класс уровня

public:
    LevelScene() = default;
    LevelScene(int levelNumber);
    void update() override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
};

}  // namespace super_hse

#endif  // SCENE_HPP_
