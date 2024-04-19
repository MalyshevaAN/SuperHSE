#ifndef INPUT_BOX_HPP_
#define INPUT_BOX_HPP_

#include <SFML/Graphics.hpp>

namespace super_hse {

enum class InputBoxType { Username, Password };

class InputBox {
public:
    std::string textString;
    sf::RectangleShape box;
    sf::Text inputText;
    sf::Text label;
    bool mustBeHidden = false;
    InputBoxType type;

    void init(const sf::Font &font, const InputBoxType box_type);
    void draw(sf::RenderWindow &window);
    void setPosition();
};

}  // namespace super_hse

#endif  // INPUT_BOX_HPP_
