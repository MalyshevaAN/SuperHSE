#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <vector>


int main(){
    sf::IpAddress ip = sf::IpAddress::getLocalAddress(); // if wee need to work from different computers - then sf::IpAddress("your ip")
    sf::TcpSocket socket;
    bool done = false;
    std::string username;
    std::string text = "";
    std::cout << "Enter online username: ";
    std::cin >> username;
    socket.connect(ip, 2000);

    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Chat");
    std::vector<sf::Text> chat;
    sf::Packet packet;
    packet << username;
    socket.send(packet);
    socket.setBlocking(false);

    window.setTitle(username);

    sf::Font font;
    font.loadFromFile("../assets/fonts/Arial.ttf");

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape){
                        window.close();
                    }
                    else if (event.key.code == sf::Keyboard::Return){
                        sf::Packet packet;
                        packet << text;
                        std::cout << text << '\n';
                        socket.send(packet);
                        sf::Text displayText(text, font, 20);
                        displayText.setColor(sf::Color::Green);
                        chat.push_back(displayText);
                        text = "";
                    }
                    break;
                case sf::Event::TextEntered:
                    text += event.text.unicode;
                    break;
            }
        }

        sf::Packet packet;
        socket.receive(packet);
        std::string temptext;
        if(packet >> temptext){
            std::cout << temptext << '\n';
            sf::Text displayText(temptext, font, 20);
            displayText.setColor(sf::Color::Red);
            chat.push_back(displayText);
        }
        window.clear();
        int i = 0;
        for (i; i < chat.size(); ++i){
            chat[i].setPosition(0, i*25);
            window.draw(chat[i]);
        }

        sf::Text drawText(text, font, 20);
        drawText.setColor(sf::Color::Blue);
        drawText.setPosition(0, i*25);
        window.draw(drawText);
        window.display();
    }
}
