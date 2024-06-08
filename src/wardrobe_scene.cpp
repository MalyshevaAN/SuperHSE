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
    colorIcons.resize(4);
    get_texture_from_file("red_square.png", colorIcons[0].texture);
    get_texture_from_file("blue_square.png", colorIcons[1].texture);
    get_texture_from_file("white_square.png", colorIcons[2].texture);
    get_texture_from_file("purple_square.png", colorIcons[3].texture);
    for (auto &colorIcon : colorIcons) {
        colorIcon.sprite.setTexture(colorIcon.texture);
        colorIcon.sprite.setScale(2, 2);
    }

    if (isSkinAvailable(Game::player_id, 8)) {
        int current_skin = getCurrentSkinNum(Game::player_id);
        switch (current_skin) {
            case 8: {
                get_texture_from_file("skin8_current.png", Sashok.texture);
                break;
            }
            case 9: {
                get_texture_from_file("skin9_current.png", Sashok.texture);
                break;
            }
            case 10: {
                get_texture_from_file("skin10_current.png", Sashok.texture);
                break;
            }
            case 11: {
                get_texture_from_file("skin11_current.png", Sashok.texture);
                break;
            }
            default: {
                get_texture_from_file("skin8_available.png", Sashok.texture);
            }
        }
    } else {
        get_texture_from_file("skin8_unavailable.png", Sashok.texture);
    }

    Sashok.sprite.setTexture(Sashok.texture);
    Sashok.sprite.setScale(1, 1);

    get_texture_from_file("HSEcoin.png", HSEcoin.texture);
    HSEcoin.sprite.setTexture(HSEcoin.texture);
    HSEcoin.sprite.setTextureRect({0, 0, 16, 16});
    HSEcoin.sprite.setScale(2, 2);
    SashokCost.setFont(font_8bit);
    SashokCost.setCharacterSize(25);
    SashokCost.setFillColor(sf::Color::Black);
    SashokCost.setString(std::to_string(getSkinCost(8)));

    skinIcons.resize(Game::simpleSkinsCount);
    for (int i = 0; i < Game::simpleSkinsCount; ++i) {
        skinIcons[i] = skinIcon(i + 1);
    }

    get_texture_from_file("HSEcoin.png", CoinTexture);
    coin.setTexture(CoinTexture);
    coin.setTextureRect({0, 0, 16, 16});
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
    balance.setString(std::to_string(getBalance(Game::player_id)));

    instruction.setFont(font_8bit);
    instruction.setCharacterSize(25);
    instruction.setFillColor(sf::Color::Black);
    instruction.setString(
        "Press skin's icon to buy or apply. New skin will be applied "
        "automatically"
    );

    error.setFont(font_8bit);
    error.setCharacterSize(35);
    error.setFillColor(sf::Color::Red);
    error.setString("Oops! Go and earn more HSEcoins!");

    updateSceneSize();
}

void WardrobeScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (const auto &skin : skinIcons) {
                if (skin.skinIconSprite.getGlobalBounds().contains(
                        event.mouseButton.x, event.mouseButton.y
                    )) {
                    Game::errorOn = false;
                    if (skin.available && !skin.current) {
                        SceneManager::changeScene(
                            std::make_unique<MainMenuScene>()
                        );
                        updateSkin(Game::player_id, skin.number);
                        SceneManager::changeScene(
                            std::make_unique<WardrobeScene>()
                        );
                    } else if (!skin.available) {
                        bool ok =
                            (getBalance(Game::player_id) >=
                             getSkinCost(skin.number));
                        if (ok) {
                            buySkin(Game::player_id, skin.number);
                        } else {
                            Game::errorOn = true;
                        }
                        SceneManager::changeScene(
                            std::make_unique<WardrobeScene>()
                        );
                    }
                    return;
                }
            }
            if (Sashok.sprite.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                Game::errorOn = false;
                if (isSkinAvailable(Game::player_id, 8) &&
                    getCurrentSkinNum(Game::player_id) < 8) {
                    SceneManager::changeScene(std::make_unique<MainMenuScene>()
                    );
                    updateSkin(Game::player_id, 8);
                    SceneManager::changeScene(std::make_unique<WardrobeScene>()
                    );
                } else if (!isSkinAvailable(Game::player_id, 8)) {
                    bool ok = (getBalance(Game::player_id) >= getSkinCost(8));
                    if (ok) {
                        buySkin(Game::player_id, 8);
                    } else {
                        Game::errorOn = true;
                    }
                    SceneManager::changeScene(std::make_unique<WardrobeScene>()
                    );
                }
                return;
            }

            Game::errorOn = false;
            for (int i = 0; i < 4; ++i) {
                if (colorIcons[i].sprite.getGlobalBounds().contains(
                        event.mouseButton.x, event.mouseButton.y
                    )) {
                    if (!isSkinAvailable(Game::player_id, 8)) {
                        Game::errorOn = true;
                        continue;
                    }
                    SceneManager::changeScene(std::make_unique<MainMenuScene>()
                    );
                    updateSkin(Game::player_id, i + 8);
                    SceneManager::changeScene(std::make_unique<WardrobeScene>()
                    );
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
    Game::backButton.setPosition(20, 20);
    Game::soundButton.setPosition(
        Game::backButton.getPosition().x +
            Game::backButton.getGlobalBounds().width + 20,
        20
    );

    float buttonWidth = 126.0f;
    float buttonHeight = 126.0f;
    float distanceBetweenButtons = (Game::windowWidth - 4 * buttonWidth) / 5;

    for (auto &skin : skinIcons) {
        skin.skinIconSprite.setPosition(
            distanceBetweenButtons * ((skin.number - 1) % 4 + 1) +
                ((skin.number - 1) % 4) * buttonWidth,
            ((skin.number + 3) / 4) *
                    ((Game::windowHeight - 2 * buttonHeight) / 3) +
                ((skin.number + 3) / 4 - 1) * buttonHeight
        );

        if (!skin.available) {
            skin.HSEcoinSprite.setTexture(skin.HSEcoinTexture);
            skin.HSEcoinSprite.setTextureRect({0, 0, 16, 16});

            skin.HSEcoinSprite.setPosition(
                distanceBetweenButtons * ((skin.number - 1) % 4 + 1) +
                    ((skin.number - 1) % 4) * buttonWidth + buttonWidth / 5,
                ((skin.number + 3) / 4) *
                        ((Game::windowHeight - 2 * buttonHeight) / 3) +
                    ((skin.number + 3) / 4 - 1) * buttonHeight +
                    buttonHeight * 1.1
            );

            skin.HSEcoinSprite.setScale(2, 2);
            skin.skinCost.setPosition(
                distanceBetweenButtons * ((skin.number - 1) % 4 + 1) +
                    ((skin.number - 1) % 4) * buttonWidth +
                    skin.HSEcoinSprite.getTexture()->getSize().x * 0.8,
                ((skin.number + 3) / 4) *
                        ((Game::windowHeight - 2 * buttonHeight) / 3) +
                    ((skin.number + 3) / 4 - 1) * buttonHeight +
                    buttonHeight * 1.1
            );
        }
    }

    Sashok.sprite.setPosition(
        distanceBetweenButtons * 4 + 3 * buttonWidth,
        2 * ((Game::windowHeight - 2 * buttonHeight) / 3) + buttonHeight
    );

    HSEcoin.sprite.setPosition(
        distanceBetweenButtons * 4 + 3 * buttonWidth + buttonWidth / 5,
        2 * ((Game::windowHeight - 2 * buttonHeight) / 3) + buttonHeight +
            buttonHeight * 1.1
    );

    SashokCost.setPosition(
        distanceBetweenButtons * 4 + 3 * buttonWidth +
            HSEcoin.sprite.getTexture()->getSize().x * 0.8,
        2 * ((Game::windowHeight - 2 * buttonHeight) / 3) + buttonHeight +
            buttonHeight * 1.1
    );

    float square = 32.0f;

    for (int i = 0; i < 4; ++i) {
        colorIcons[i].sprite.setPosition(
            distanceBetweenButtons * 4 + 3 * buttonWidth + i * square - 1,
            2 * ((Game::windowHeight - 2 * buttonHeight) / 3) + buttonHeight -
                square
        );
    }

    float windowCenterX = Game::windowWidth / 2.0f;
    float textWidth = instruction.getLocalBounds().width;
    instruction.setPosition(
        windowCenterX - textWidth / 2.0f, Game::windowHeight * 6 / 7
    );
    balance.setPosition(
        Game::windowWidth - 2 * coin.getTexture()->getSize().x,
        coin.getTexture()->getSize().y
    );
    coin.setPosition(
        Game::windowWidth - 3 * coin.getTexture()->getSize().x,
        coin.getTexture()->getSize().y
    );
}

void WardrobeScene::draw(sf::RenderWindow &window) {
    sf::View view;
    view.setSize(Game::windowWidth, Game::windowHeight);
    view.setCenter(Game::windowWidth / 2, Game::windowHeight / 2);
    window.clear(backgroundColor);
    window.setView(view);

    float windowCenterX = window.getSize().x / 2.0f;
    float instructionTextWidth = instruction.getLocalBounds().width;
    float errorTextWidth = error.getLocalBounds().width;
    instruction.setPosition(
        windowCenterX - instructionTextWidth / 2.0f, window.getSize().y * 6 / 7
    );
    error.setPosition(
        windowCenterX - errorTextWidth / 2.0f, window.getSize().y / 2.0f
    );
    balance.setPosition(
        window.getSize().x - 2 * coin.getTexture()->getSize().x,
        coin.getTexture()->getSize().y
    );
    coin.setPosition(
        window.getSize().x - 3 * coin.getTexture()->getSize().x,
        coin.getTexture()->getSize().y
    );

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
            skin.skinCost.setCharacterSize(25);
            skin.skinCost.setFillColor(sf::Color::Black);
            skin.skinCost.setString(std::to_string(skin.cost));
        }
        skin.skinIconSprite.setScale(1, 1);
        window.draw(skin.skinIconSprite);
        window.draw(skin.skinCost);
        window.draw(skin.HSEcoinSprite);
    }

    for (auto color : colorIcons) {
        window.draw(color.sprite);
    }
    window.draw(Sashok.sprite);
    if (!isSkinAvailable(Game::player_id, 8)) {
        window.draw(HSEcoin.sprite);
        window.draw(SashokCost);
    }

    window.draw(coin);
    window.draw(balance);
    window.draw(Game::backButton);
    window.draw(Game::soundButton);
    window.draw(instruction);
    if (Game::errorOn) {
        window.draw(error);
    }
    window.display();
}

}  // namespace super_hse
