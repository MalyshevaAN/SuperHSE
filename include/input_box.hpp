#ifndef INPUT_BOX_HPP_
#define INPUT_BOX_HPP_

#include <SFML/Graphics.hpp>

namespace super_hse {

enum class InputBoxType { Username, Password };

class InputBox {
public:
    sf::RectangleShape box;
    sf::Text inputText;
    sf::Text label;
    bool mustBeHidden = false;
    InputBoxType type;

    void init(const sf::Font &font, const InputBoxType box_type);
};

}

#endif  // INPUT_BOX_HPP_
