#ifndef CLIENT_CPP
#define CLIENT_CPP

#include "client.hpp"
#include "hse_utils.hpp"
#include <iostream>

namespace super_hse{
void client::init(const std::string &server_ip_, const unsigned int server_port_){
    serverIp = sf::IpAddress(server_ip_); // в будущем данные с клавиатуры
    serverPort = server_port_;
    if (socket.connect(serverIp, serverPort) != sf::Socket::Done){
        throw connectionException(serverIp.toString()+ ":" + std::to_string(serverPort));
    }
    std::string message = "Hello from the client!\n";
    sf::Packet packet;
    packet << message;
    if (socket.send(packet) != sf::Socket::Done){
        throw sendingException();
    }
    std::cout << "Data sent to server\n";
}

void client::send(){

}

void client::get(){

}

}

#endif
