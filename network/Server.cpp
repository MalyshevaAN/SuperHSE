#ifndef SERVER_CPP
#define SERVER_CPP

#include "server.hpp"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include "messages.hpp"
#include "cstring"
#include <algorithm>
#include <thread>

namespace super_hse{

server::server(): serverIp(sf::IpAddress::getLocalAddress()), serverPort1(8000), serverPort2(8001){
    std::cout << "Server Address " << sf::IpAddress::getLocalAddress().toString() << '\n';
    std::cout << "Server is listening on port " << serverPort1 << '\n';
    std::cout << "Server is listening on port " << serverPort2 << '\n';
    std::filesystem::path p(std::filesystem::current_path());
    entities.init(p.parent_path().string() + "/assets/files/multi_level.txt");
    players.resize(2);
};

void server::waitForConnection(int player){
    sf::Packet server_state;
    if (player == 1){
        listener1.listen(serverPort1);
        listener1.accept(socket1);
        state = SERVER_STATE::WAIT_FOR_SECOND_CONNECTION;
        server_state << 1;
        socket1.send(server_state);

    } 
    if (player == 2){
        listener2.listen(serverPort2);
        listener2.accept(socket2);
        state = SERVER_STATE::CONNECTED;
        server_state << 2;
        socket1.send(server_state);
        socket2.send(server_state);
    }
    std::cerr << "Get new Client!\n";
}

void server::update_player_state_and_send(query &query_, answer &answer_, sf::FloatRect &nextPositionCollider, int index){
        players[index].x = nextPositionCollider.left;
        players[index].y = nextPositionCollider.top;
        players[index].skin_col = query_.skin_col;
        players[index].skin_row = query_.skin_row;
        players[index].skin_id = query_.skin_id;
        if (answer_.gathered_coin_index != -1){
            players[index].gathered_coin_id = answer_.gathered_coin_index;
        }
        if(answer_.killed_enemy_index != -1){
            players[index].killed_enemy_id = answer_.killed_enemy_index;
        }
        int partner_index = (index + 1)% 2;
        answer_.x_partner = players[partner_index].x;
        answer_.y_partner = players[partner_index].y;
        answer_.skin_col_partner = players[partner_index].skin_col;
        answer_.skin_row_partner = players[partner_index].skin_row;
        answer_.skin_id_partner = players[partner_index].skin_id;
        answer_.gathered_coin_index_partner = players[partner_index].gathered_coin_id;
        answer_.killed_enemy_index_partner = players[partner_index].killed_enemy_id;
        sf::Packet sendPacket;
        answer_.fill_answer(sendPacket);
        if (index == 0){
            socket1.send(sendPacket);
        }else {
            socket2.send(sendPacket);
        }
}

void server::updateScene(int num){
    bool is_connected = true;
    while(is_connected){
        if (socket1.getRemoteAddress() == sf::IpAddress::None
        || socket2.getRemoteAddress() == sf::IpAddress::None){
            is_connected = false;
            socket1.disconnect();
            socket2.disconnect();
            state = SERVER_STATE::WAIT_FOR_FIRST_CONNECTION;
            std::cerr << "Clients are not available\n";
            continue;
        }
        sf::Packet getPacket;
        if (num == 0){
            socket1.receive(getPacket);
        }else{
            socket2.receive(getPacket);
        }
            struct query query_;
            query_.get_query_from_packet(getPacket);
            sf::FloatRect nextPositionCollider(query_.nextPositionColliderLeft, query_.nextPositionColliderTop, query_.nextPositionColliderWidth, query_.nextPositionColliderHeight);
            sf::Vector2f movement(query_.movement_x, query_.movement_y);
            for (auto elem : entities.enemies){
                elem.change_pos();
            }
            answer answer_ = entities.update(nextPositionCollider, movement);
            std::unique_lock l(m);
            update_player_state_and_send(query_, answer_, nextPositionCollider, num);
            l.unlock();
    }
}

void server::updateSceneWrapper(server* serverObj, int num){
    serverObj->updateScene(num);
}

void server::run() {
    while (true) {
        switch (state) {
            case SERVER_STATE::WAIT_FOR_FIRST_CONNECTION:
                waitForConnection(1);
                break;
            case SERVER_STATE::WAIT_FOR_SECOND_CONNECTION:
                waitForConnection(2);
                break;  
            case SERVER_STATE::CONNECTED:
                if (!game_started){
                    std::thread th1(&server::updateSceneWrapper, this, 0);
                    std::thread th2(&server::updateSceneWrapper, this, 1);
                    game_started = true;
                    th1.join(); 
                    th2.join(); 
                }

                break;
        }
    }
}


}

#endif
