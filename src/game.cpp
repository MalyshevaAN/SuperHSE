#include "game.hpp"
#include "scene.hpp"
#include <memory>

namespace super_hse {

void Game::run() {
    sceneManager.changeScene(std::make_unique<MainMenuScene>());

    while (window.isOpen()) {
        sceneManager.handleInput(window);
        sceneManager.update();
        sceneManager.draw(window);
    }  
}

} // namespace super_hse
