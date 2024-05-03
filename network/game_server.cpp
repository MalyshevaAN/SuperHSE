#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <vector>

int main(){
    sf::IpAddress serverIp = sf::IpAddress("127.0.0.1");
    int serverPort = 8000;
    sf::TcpSocket socket;


    sf::TcpListener listener;
    listener.listen(serverPort);
    if (listener.accept(socket) != sf::Socket::Done){
        std::cerr << "Failed to bind listener socket to port 8000\n";
        return -1;
    };
    std::cout<<"Server is listening on port 8000\n";

    socket.setBlocking(false);
    while(true){
        sf::Packet packet;
        socket.receive(packet);
        std::string message;
        packet >> message;
        std::cout << message;
    }
    return 0;
}
