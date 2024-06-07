#ifndef SERVER_INFO_WINDOW_HPP_
#define SERVER_INFO_WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "string"

namespace super_hse {

struct ServerInfoScene : public Scene {
private:
    std::string serverIP;
    std::pair<int, int> ports;

    sf::Texture logoPicture;
    sf::Sprite logo;

    sf::Font font;
    sf::Text ipText;
    sf::Text port1;
    sf::Text port2;

    sf::RenderWindow window;
    const sf::Color backgroundColor = sf::Color(154, 217, 234);

public:
    ServerInfoScene();

    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;

    void init();
    void run();

    int windowWidth = 1180;
    int windowHeight = 760;
};

}  // namespace super_hse

#endif  // SERVER_INFO_WINDOW_HPP_