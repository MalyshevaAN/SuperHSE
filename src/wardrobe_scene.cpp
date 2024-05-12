#include "wardrobe_scene.hpp"
#include <filesystem>
#include <memory>
#include "game.hpp"
#include "hse_utils.hpp"
#include "main_menu_scene.hpp"
#include "scene.hpp"
#include "sql.hpp"

namespace super_hse {

WardrobeScene::WardrobeScene() {
    skinIcons.resize(Game::skinsCount);
    for (int i = 0; i < Game::skinsCount; ++i) {
        skinIcons[i] = skinIcon(i + 1);
    }

    get_texture_from_file("HSEcoin.png", CoinTexture);
    coin.setTexture(CoinTexture);
    coin.setTextureRect({0,0,16,16});
    coin.setPosition(Game::windowWidth - 5 * coin.getTexture()->getSize().x, coin.getTexture()->getSize().y);
    coin.setScale(3, 3);

    if (!font.loadFromFile("../assets/fonts/Karma.ttf")) {
        std::cerr << "Error loading font\n";
    }
    if (!font_8bit.loadFromFile("../assets/fonts/8bit.ttf")) {
        std::cerr << "Error loading font\n";
    }
    balance.setFont(font);
    balance.setCharacterSize(30);
    balance.setFillColor(sf::Color::Black);
    balance.setPosition(Game::windowWidth - 3 * coin.getTexture()->getSize().x, coin.getTexture()->getSize().y);
    balance.setString(std::to_string(getBalance(Game::player_id)));

    updateSceneSize();
}

void WardrobeScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (const auto &skin : skinIcons) {
                if (skin.skinIconSprite.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y)) {
                    if (skin.available && !skin.current) {
                        SceneManager::changeScene(std::make_unique<MainMenuScene>());
                        updateSkin(Game::player_id, skin.number);
                    } else if (!skin.available) {
                        SceneManager::changeScene(std::make_unique<MainMenuScene>());
                        bool success = buySkin(Game::player_id, skin.number); // TODO input not enough cash
                        if (!success) {
                            std::cerr << "Oops... Go and earn more money\n";
                        }
                    }
                    return;
                }
            }
            if (Game::backButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
        }
    }
}

void WardrobeScene::update(sf::Time &dTime) {
}

void WardrobeScene::updateSceneSize() {
    float buttonWidth = 126.0f;
    float buttonHeight = 126.0f;
    float distanceBetweenButtons = (Game::windowWidth - 3 * buttonWidth) / 4;


    // TODO add costs
    for (auto &skin : skinIcons) {
        skin.skinIconSprite.setPosition(
            distanceBetweenButtons * ((skin.number - 9) % 3 + 3) + ((skin.number - 1) % 3) * buttonWidth,
            ((skin.number + 2) / 3) * ((Game::windowHeight - 2 * buttonHeight) / 3) + ((skin.number + 2) / 3 - 1) * buttonHeight
        );
        if (!skin.available){
            skin.HSEcoinSprite.setTexture(skin.HSEcoinTexture);
            skin.HSEcoinSprite.setTextureRect({0,0,16,16});

            skin.HSEcoinSprite.setPosition(
                distanceBetweenButtons * ((skin.number - 9) % 3 + 3) + ((skin.number - 1) % 3) * buttonWidth,
                ((skin.number + 2) / 3) * ((Game::windowHeight - 2 * buttonHeight) / 3) + ((skin.number + 2) / 3 - 1) * buttonHeight + buttonHeight
            );

            skin.HSEcoinSprite.setScale(3, 3);

            skin.skinCost.setPosition(
                distanceBetweenButtons * ((skin.number - 9) % 3 + 3) + ((skin.number - 1) % 3) * buttonWidth + skin.HSEcoinSprite.getTexture()->getSize().x,
                ((skin.number + 2) / 3) * ((Game::windowHeight - 2 * buttonHeight) / 3) + ((skin.number + 2) / 3 - 1) * buttonHeight + buttonHeight
            );
        }
    }
}

void WardrobeScene::draw(sf::RenderWindow &window) {
    sf::View view;
    view.setSize(Game::windowWidth, Game::windowHeight);
    view.setCenter(Game::windowWidth / 2, Game::windowHeight / 2);
    window.clear(backgroundColor);
    window.setView(view);

    for (auto &skin : skinIcons) {
        if (skin.available) {
            if (skin.current) {
                skin.skinIconSprite.setTexture(skin.skinIconTextureCurrent);
            } else {
                skin.skinIconSprite.setTexture(skin.skinIconTextureAvailable);
            }
        } else {
            skin.skinIconSprite.setTexture(skin.skinIconTextureUnavailable);
            skin.skinCost.setFont(font_8bit);
            skin.skinCost.setCharacterSize(30);
            skin.skinCost.setFillColor(sf::Color::Black);
            skin.skinCost.setString(std::to_string(skin.cost));
        }
        skin.skinIconSprite.setScale(0.8, 0.8);
        window.draw(skin.skinIconSprite);
        window.draw(skin.skinCost);
        window.draw(skin.HSEcoinSprite);
    }
    
    window.draw(coin);
    window.draw(balance);
    window.draw(Game::backButton);
    window.display();
}

}  // namespace super_hse
