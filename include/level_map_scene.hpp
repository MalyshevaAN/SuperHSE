#ifndef LEVEL_MAP_SCENE_HPP_
#define LEVEL_MAP_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "level_icon.hpp"
#include "scene.hpp"

namespace super_hse {

class LevelMapScene : public Scene {
private:
    sf::Texture clothesPicture;
    sf::Texture levelMapTexture;

    sf::Sprite clothes;
    sf::Sprite levelMap;

    std::vector<levelIcon> levelIcons;

    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public:
    LevelMapScene();
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // LEVEL_MAP_SCENE_HPP_
