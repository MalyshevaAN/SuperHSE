#ifndef SERVER_CPP
#define SERVER_CPP

#include "server.hpp"
#include <iostream>

namespace super_hse{
server::server(): serverIp(sf::IpAddress("127.0.0.1")), serverPort(8000){
    std::cout << "Server is listening on port " << serverPort << '\n';
};

void server::waitForConnection(){
    listener.listen(serverPort);
    listener.accept(socket);
    std::cerr << "Get new Client!\n";
    state = SERVER_STATE::CONNECTED;
}

void server::updateScene(){
    int x;
    int y;
    sf::Packet new_packet, get_packet;
    socket.receive(new_packet);
    if (new_packet >> x >> y){
        get_packet << x << y;
        socket.send(get_packet);
    }
}

void server::run(){
    while (true){
        switch (state){
            case SERVER_STATE::WAIT_FOR_CONNECTION:
                waitForConnection();
                break;
            case SERVER_STATE::CONNECTED:
                updateScene();
        }
    }
}

}

#endif
