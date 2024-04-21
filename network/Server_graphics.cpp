#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
//#include <windows.h>

int main(){
    sf::IpAddress ip = sf::IpAddress::getLocalAddress(); // what if different computer?
    sf::TcpSocket socket;
    char connectionType;
    char buffer[2000];
    std::size_t received;
    std::cout << "Enter (s) for Server, Enter (c) for client" << std::endl;
    std::cin >> connectionType;
    if (connectionType == 's'){
        sf::TcpListener listener;
        listener.listen(2100);
        listener.accept(socket);
    }else if (connectionType == 'c'){
        socket.connect(ip, 2100);
    }
    sf::RectangleShape rect1, rect2;
    rect1.setSize(sf::Vector2f(20, 20));
    rect2.setSize(sf::Vector2f(20, 20));

    rect1.setFillColor(sf::Color::Blue);
    rect2.setFillColor(sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Packets");
    sf::Vector2f prevPosition, p2Position;
    socket.setBlocking(false);

    bool update = false;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }else if(event.type == sf::Event::GainedFocus){
                update = true;
            }else if(event.type == sf::Event::LostFocus){
                update = false;
            }
        }
        prevPosition = rect1.getPosition();
        if (update){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                rect1.move(0.5f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                rect1.move(-0.5f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                rect1.move(0.0f, -0.5f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                rect1.move(0.0f, 0.5f);
            }
        }
        sf::Packet packet;
        if (prevPosition != rect1.getPosition()){
            packet << rect1.getPosition().x << rect1.getPosition().y;
            socket.send(packet);
        }

        socket.receive(packet);
        if (packet >> p2Position.x >> p2Position.y){
            rect2.setPosition(p2Position);
        }

        window.clear();
        window.draw(rect1);
        window.draw(rect2);
        window.display();
    }
}


