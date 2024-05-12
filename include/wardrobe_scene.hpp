#ifndef WARDROBE_SCENE_HPP_
#define WARDROBE_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include <vector>
#include "skin_icon.hpp"
#include "input_box.hpp"

namespace super_hse {

class WardrobeScene : public Scene {
private:
    std::vector<skinIcon> skinIcons;

    sf::Font font;
    sf::Font font_8bit;
    sf::Text balance;

    sf::Texture CoinTexture;
    sf::Sprite coin;

    sf::Text instruction;

    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public:
    WardrobeScene();
    
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // WARDROBE_SCENE_HPP_
