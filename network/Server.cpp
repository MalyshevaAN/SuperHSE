#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
//#include <windows.h>

int main(){
    sf::IpAddress ip = sf::IpAddress::getLocalAddress(); // what if different computer?
    sf::TcpSocket socket;
    char connectionType, mode;
    char buffer[2000];
    std::size_t received;
    std::cout << "Enter (s) for Server, Enter (c) for client" << std::endl;
    std::cin >> connectionType;
    std::string text = "Connected to: ";
    if (connectionType == 's'){
        sf::TcpListener listener;
        listener.listen(2100);
        listener.accept(socket);
        text += "Server";
        mode = 's';
    }else if (connectionType == 'c'){
        socket.connect(ip, 2100);
        text += "Client";
        mode = 'r';
    }
    socket.send(text.c_str(), text.length() + 1);
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << buffer << std::endl;
    bool done = false;
    while (!done){
        if (mode == 's'){
            std::getline(std::cin, text);
            socket.send(text.c_str(), text.length() + 1);
            mode = 'r';
        }else if (mode == 'r'){
            socket.receive(buffer, sizeof(buffer), received);
            if (received > 0){
                std::cout << "Received: " << buffer << std::endl;
                mode = 's';
            }
        }
    }
}


