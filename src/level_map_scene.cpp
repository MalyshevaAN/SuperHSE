#include <memory>
#include "scene.hpp"
#include <filesystem>

namespace super_hse {

LevelMapScene::LevelMapScene() {
    std::filesystem::path p(std::filesystem::current_path());
    if (!levelMapPicture.loadFromFile(p.parent_path().string() + "/assets/images/ryan2.png")) {
        std::cerr << "Error loading level_map.png\n";
    }
    label.setTexture(levelMapPicture);
    // тут инициализируем все что нужно в этой сцене
    label.setPosition(100, 100);
}

void LevelMapScene::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            SceneManager::changeScene(std::make_unique<LevelScene>(0));

            return;
        } else if (event.key.code == sf::Keyboard::M) {
            SceneManager::changeScene(std::make_unique<MainMenuScene>());
            return;
        }
    }
}

void LevelMapScene::update(sf::Time &dTime) {
}

void LevelMapScene::draw(sf::RenderWindow &window) {
    window.clear();
    window.draw(label);
    window.display();
}

}  // namespace super_hse
