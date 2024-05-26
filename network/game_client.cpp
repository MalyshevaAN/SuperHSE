#ifndef CLIENT_CPP
#define CLIENT_CPP

#include "client.hpp"
#include "hse_utils.hpp"
#include <iostream>
#include "cstring"

namespace super_hse{
void client::init(const std::string &server_ip_, const unsigned int server_port_){
    serverIp = sf::IpAddress(server_ip_); // в будущем данные с клавиатуры
    serverPort = server_port_;
    if (socket.connect(serverIp, serverPort, sf::seconds(1)) != sf::Socket::Done) { // 5 секунд таймаут
        socket.disconnect();
        state = CONNECTION_STATE::IS_NOT_CONNECTED;
        return;
    }
    state = CONNECTION_STATE::READY_TO_PLAY;
    std::cout << "Data sent to server\n";
}

CONNECTION_STATE client::get_connection_state(){
    sf::Packet send_packet, get_packet;
    send_packet << "q";
    socket.send(send_packet);
    if(socket.receive(get_packet) == sf::Socket::Done){
        int kol;
        get_packet >> kol;
        if (kol == 2){
            return CONNECTION_STATE::READY_TO_PLAY;
        }else{
            return CONNECTION_STATE::WAITING_FOR_PARTER;
        }
    }else{
        return CONNECTION_STATE::IS_NOT_CONNECTED;
    }
}

answer client::send(query &query_){
    sf::Packet sendPacket, getPacket;
    //sendPacket << query_.nextPositionColliderLeft << query_.nextPositionColliderTop <<  query_.nextPositionColliderWidth <<  query_.nextPositionColliderHeight << query_.movement_x << query_.movement_y;
    query_.fill_query(sendPacket);
    socket.send(sendPacket);
    socket.receive(getPacket);
    answer answer_;
    answer_.get_answer_from_packet(getPacket);
    //getPacket >> answer_.isCollidingWithWall >> answer_.isCollidingWithFloor >> answer_.movement_x >> answer_.movement_y >> answer_.lose_life >> answer_.gathered_coin_index >> answer_.killed_enemy_index >> answer_.run_into_enemy_index;
    //std::memcpy(&answer_, getPacket.getData(), getPacket.getDataSize());
    return answer_;
}

void client::get(){

}

}

#endif
