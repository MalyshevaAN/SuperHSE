#ifndef SERVER_CPP
#define SERVER_CPP

#include "server.hpp"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

namespace super_hse{

server::server(): serverIp(sf::IpAddress("127.0.0.1")), serverPort(8000){
    std::cout << "Server is listening on port " << serverPort << '\n';
    std::filesystem::path p(std::filesystem::current_path());
    entities.init(p.parent_path().string() + "/assets/files/multi_level.txt");
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
    int width;
    int height;
    int dx;
    int dy;
    sf::Packet new_packet, get_packet;
    socket.receive(new_packet);
    if (new_packet >> x >> y >> width >> height >> dx >> dy){
        sf::FloatRect nextPositionCollider(x, y, width, height);
        sf::Vector2f movement(dx, dy);
        std::pair<bool, bool> collision = entities.check_collider_collision(nextPositionCollider, movement);
        get_packet << collision.first << collision.second;
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
