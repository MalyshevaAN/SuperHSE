#ifndef WIN_SCENE_HPP
#define WIN_SCENE_HPP

#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace super_hse {
class WinScene : public Scene {
private:
    sf::Texture BackgroundTexture;
    sf::Texture NextLevelTexture;
    sf::Texture MainMenuTexture;
    sf::Texture TryAgainTexture;
    sf::Texture CoinTexture;
    sf::Texture LivesTexture;
    sf::Texture GraduateTexture;

    sf::Sprite background;
    sf::Sprite nextLevel;
    sf::Sprite mainMenu;
    sf::Sprite tryAgain;
    sf::Sprite coin;
    sf::Sprite lives;
    sf::Sprite graduate;

    sf::Font font;

    sf::Text saved_lives_count;
    sf::Text collected_coins;
    sf::Text records_txt;
    sf::Text best_lives;
    sf::Text best_coins;
    sf::Text result_txt;

    int coins;
    int level_numb;
    int saved_lives;
    char state;

    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public:
    WinScene();
    WinScene(int coins_, int level_numb_, int saved_lives_, char state_);
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};
}  // namespace super_hse

#endif
