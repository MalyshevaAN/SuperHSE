#ifndef SERVER_CPP
#define SERVER_CPP

#include "server.hpp"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include "messages.hpp"
#include "cstring"
#include <algorithm>

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
    sf::Packet getPacket;
    socket.receive(getPacket);
    struct query query_;
    //std::memcpy(&query_, getPacket.getData() , sizeof(query));
    query_.get_query_from_packet(getPacket);
    sf::FloatRect nextPositionCollider(query_.nextPositionColliderLeft, query_.nextPositionColliderTop, query_.nextPositionColliderWidth, query_.nextPositionColliderHeight);
    sf::Vector2f movement(query_.movement_x, query_.movement_y);
    answer answer_ = entities.update(nextPositionCollider, movement);
    sf::Packet sendPacket;
    answer_.fill_answer(sendPacket);
    //sendPacket << answer_.isCollidingWithWall << answer_.isCollidingWithFloor << answer_.movement_x <<answer_.movement_y <<answer_.lose_life << answer_.gathered_coin_index << answer_.killed_enemy_index << answer_.run_into_enemy_index;
    socket.send(sendPacket);
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
