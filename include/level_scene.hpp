#ifndef LEVEL_SCENE_HPP_
#define LEVEL_SCENE_HPP_

#include "scene.hpp"

namespace super_hse {

class LevelScene : public Scene {
private:
    std::string ldtk_filename;
    Player player;
    LevelsStorage storage;
    int levelNumber;
    Level level;  // добавила класс уровня

    const sf::Color windowFillColor = sf::Color(125, 166, 218);

public:
    LevelScene() = default;
    LevelScene(std::string ldtk_filename);
    LevelScene(int levelN);
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}

#endif // LEVEL_SCENE_HPP_
