#include <LDtkLoader/Project.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "Level.hpp"
#include "TileMap.hpp"
#include "scene.hpp"

namespace super_hse {

LevelScene::LevelScene(std::string filename) {
    // player = Player();

    level.ldtk_filename = filename;
    level.project.loadFromFile(filename);
    level.init();
}

void LevelScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::L) {
            SceneManager::changeScene(std::make_unique<LevelMapScene>());
            return;
        } else if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }
    // player.handleInput(event);
}

void LevelScene::update(sf::Time &dTime) {
    // level.update() - пока нет

    player.update(dTime);

    // collision checks:
    auto player_collider = player.getCollider();
    int dTimeSeconds = dTime.asSeconds();
    for (auto &entity: level.colliders) {
        sf::FloatRect intersect;
        if (player_collider.intersects(entity, intersect)) {
            if (intersect.width < intersect.height) {
                if (player_collider.left < entity.left) {
                    player.move(-dTimeSeconds * player.getSpeed(), 0);
                } else {
                    player.move(dTimeSeconds * player.getSpeed(), 0);
                }
            } else {
                if (player_collider.top < entity.top) {
                    player.move(0, -dTimeSeconds * player.getSpeed());
                } else {
                    player.move(0, dTimeSeconds * player.getSpeed());
                }
            }
        }
    }
}

void LevelScene::draw(sf::RenderWindow &window) {
    window.clear();
    
    level.render(window);

    player.draw(window);
    window.display();
}

}  // namespace super_hse
