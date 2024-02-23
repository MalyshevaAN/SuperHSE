#include <iostream>
#include <SFML/Network.hpp>
#include <string>
//#include <windows.h>

int main(){
    sf::TcpSocket socket;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    if(socket.connect(ip, 2000) != sf::Socket::Done){
        std::cout << "Error!\n";
        return 0;
    }
    

    std::string name;
    std::cout << "Enter your name:\n";
    std::cin >> name;

    socket.setBlocking(false);

    std::string message = "";
    sf::Packet packet;

    while(true){
        std::cin >> message;
        if (message != ""){
            packet.clear();
            packet << name << message;
            socket.send(packet);
            message.clear();
        }

        if (socket.receive(packet) == sf::Socket::Done){
            std::string nameRec;
            std::string messageRec;

            packet >> nameRec >> messageRec;
            std::cout << nameRec << ": "<< messageRec <<'\n';
        }
    }
}


