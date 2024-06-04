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
    sf::Packet server_state;
    int active_connections;
    if (socket.receive(server_state) == sf::Socket::Done){
        server_state >> active_connections;
        if (active_connections == 1){
            state = CONNECTION_STATE::WAITING_FOR_PARTNER;
        }else if (active_connections == 2){
            state = CONNECTION_STATE::READY_TO_PLAY;
        }
    }
    std::cout << "Data sent to server\n";
}

void client::check(){
    socket.setBlocking(false);
    sf::Packet server_state;
    if (socket.receive(server_state) == sf::Socket::Done){
        int active_connections;
        server_state >> active_connections;
        if (active_connections == 2){
            state = CONNECTION_STATE::READY_TO_PLAY;
            socket.setBlocking(true);
        }
    }
}

answer client::send(query &query_){
    sf::Packet sendPacket, getPacket;
    query_.fill_query(sendPacket);
    socket.send(sendPacket);
    socket.receive(getPacket);
    answer answer_;
    answer_.get_answer_from_packet(getPacket);
    return answer_;
}

void client::get(){

}

}

#endif
