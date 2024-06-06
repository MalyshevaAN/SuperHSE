#include "server_info_scene.hpp"

namespace super_hse {

void ServerInfoScene::init() {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

void ServerInfoScene::run() {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                windowWidth = window.getSize().x;
                windowHeight = window.getSize().y;

                const sf::FloatRect visibleArea(
                    0, 0, event.size.width, event.size.height
                );
                window.setView(sf::View(visibleArea));
                updateSceneSize();
            }
        }
        draw(window);
    }
}

ServerInfoScene::ServerInfoScene()
    : window(sf::VideoMode(1080, 760), "Super HSE server") {
    if (!font.loadFromFile("../assets/fonts/8bit.ttf")) {
        std::cerr << "Error loading font\n";
    }

    get_texture_from_file("menu.png", logoPicture);
    logo.setTexture(logoPicture);

    updateSceneSize();
}

void ServerInfoScene::update(sf::Time &dTime) {
}

void ServerInfoScene::draw(sf::RenderWindow &window) {
    window.clear(backgroundColor);
    window.draw(logo);
    window.display();
}

void ServerInfoScene::handleInput(sf::Event &event) {
}

void ServerInfoScene::updateSceneSize() {
    logo.setPosition(
        (windowWidth - logoPicture.getSize().x) / 2,
        (windowHeight - logoPicture.getSize().y) / 2
    );
}

}  // namespace super_hse