#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <memory>
#include <SFML/Graphics.hpp>

namespace super_hse {

class Scene {
public:
    Scene() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void handleInput(sf::RenderWindow &window) = 0;
};

class MainMenuScene : public Scene {
public:
    MainMenuScene() = default;
    void update() override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::RenderWindow &window) override;
};

class SceneManager {
private:
    std::unique_ptr<Scene> currentScene;
public:
    void handleInput(sf::RenderWindow& window);
    void changeScene(std::unique_ptr<Scene> newScene);
    void update();
    void draw(sf::RenderWindow &window);
};

} // namespace super_hse

#endif // SCENE_HPP_
