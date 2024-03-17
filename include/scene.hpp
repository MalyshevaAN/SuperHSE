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

    virtual void update(sf::Time &dTime) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void handleInput(sf::Event &event) = 0;
    virtual void updateSceneSize() = 0;
};

class SceneManager {
private:
    // NOLINTNEXTLINE [cppcoreguidelines-avoid-non-const-global-variables]
    static std::unique_ptr<Scene> currentScene;

public:
    static void changeScene(std::unique_ptr<Scene> newScene);
    static void updateSceneSize();
    static void handleInput(sf::Event &event);
    static void update(sf::Time &dTime);
    static void draw(sf::RenderWindow &window);
};

}  // namespace super_hse

#endif  // SCENE_HPP_
