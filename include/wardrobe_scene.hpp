#ifndef WARDROBE_SCENE_HPP_
#define WARDROBE_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "input_box.hpp"
#include "scene.hpp"
#include "skin_icon.hpp"

namespace super_hse {

struct Icon {
    sf::Texture texture;
    sf::Sprite sprite;
};

class WardrobeScene : public Scene {
private:
    std::vector<skinIcon> skinIcons;
    std::vector<Icon> colorIcons;

    Icon Sashok;
    Icon HSEcoin;
    sf::Text SashokCost;

    sf::Font font;
    sf::Font font_8bit;
    sf::Text balance;

    sf::Texture CoinTexture;
    sf::Sprite coin;

    sf::Text instruction;
    sf::Text error;

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
