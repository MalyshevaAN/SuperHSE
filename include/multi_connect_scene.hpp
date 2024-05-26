#ifndef MULTI_CONNECT_SCENE_HPP_
#define MULTI_CONNECT_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "input_box.hpp"
#include "scene.hpp"

namespace super_hse {

class MultiConnectScene : public Scene {
private:
    sf::Texture bigRectanglePicture;
    sf::Sprite bigRectangle;

    InputBox ipInput;
    InputBox portInput;
    InputBox *activeInputBox = &ipInput;
    std::vector<InputBox *> inputBoxes = {&ipInput, &portInput};
    int activeInputBoxIndex = 0;

    ErrorBox errorBox;

    sf::Font font;

    sf::Texture connectButtonPicture;
    sf::Sprite connectButton;

    const sf::Color backgroundColor = sf::Color(154, 217, 234);
    const sf::Color activeInputBoxColor = sf::Color(219, 219, 219);

public:
    MultiConnectScene();

    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
    void checkAndConnect();

    void updateActiveInputText(const sf::Uint32 unicode);
    void updateInputBoxes(sf::Event &event);
};

}  // namespace super_hse

#endif  // MULTI_CONNECT_SCENE_HPP_