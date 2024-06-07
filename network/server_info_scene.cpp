#include "server_info_scene.hpp"
#include "server.hpp"

namespace super_hse {

void ServerInfoScene::init() {
    ports = getPorts();
    serverIP = sf::IpAddress::getLocalAddress().toString();

    ipText.setFont(font);
    ipText.setCharacterSize(30);
    ipText.setFillColor(sf::Color::Black);
    ipText.setString("Server IP: " + serverIP);

    port1.setFont(font);
    port1.setCharacterSize(30);
    port1.setFillColor(sf::Color::Black);
    port1.setString("Port 1: " + std::to_string(ports.first));

    port2.setFont(font);
    port2.setCharacterSize(30);
    port2.setFillColor(sf::Color::Black);
    port2.setString("Port 2: " + std::to_string(ports.second));

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
    window.draw(ipText);
    window.draw(port1);
    window.draw(port2);
    window.display();
}

void ServerInfoScene::handleInput(sf::Event &event) {
}

void ServerInfoScene::updateSceneSize() {
    logo.setPosition(
        (windowWidth - logoPicture.getSize().x) / 2,
        (windowHeight - logoPicture.getSize().y) / 2 - 100
    );
    ipText.setPosition(
        (windowWidth - ipText.getGlobalBounds().width) / 2,
        (windowHeight - ipText.getGlobalBounds().height) / 2
    );
    port1.setPosition(
        (windowWidth - port1.getGlobalBounds().width) / 2,
        (windowHeight - port1.getGlobalBounds().height) / 2 + 50
    );
    port2.setPosition(
        (windowWidth - port2.getGlobalBounds().width) / 2,
        (windowHeight - port2.getGlobalBounds().height) / 2 + 100
    );
}

}  // namespace super_hse