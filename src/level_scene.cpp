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

    // посчитаем следующую возможную позицию игрока
    sf::FloatRect nextPositionCollider = player.getCollider();
    sf::Vector2f movement = player.calcMovement(dTime);
    nextPositionCollider.left += movement.x;
    nextPositionCollider.top += movement.y;

    // Проверяем, будет ли пересечение с блоками
    int dTimeSeconds = dTime.asSeconds();

    bool isCollidingWithBlock = false;
    for (auto &entity: level.colliders) {
        sf::FloatRect intersect;
        if (nextPositionCollider.intersects(entity, intersect)) {
            // проверить тип объекта, с кем пересеклись (в данном случае - стены/пол)
            // TODO - добавить проверку на тип объекта (тут нужна Настя и её енамы)
            isCollidingWithBlock = true;
        }
        // TODO если пересечение с монетками/врагами это тоже надо 
        //      обрабатывать тут где-то (инфа на будущее)
    }

    // если не пересекается с блоками, то двигаем игрока
    if (!isCollidingWithBlock) {
        player.move(movement.x, movement.y);
    }

    // обновление фрейма
    player.update(dTime);
}

void LevelScene::draw(sf::RenderWindow &window) {
    window.clear();
    
    level.render(window);

    player.draw(window);
    window.display();
}

}  // namespace super_hse
