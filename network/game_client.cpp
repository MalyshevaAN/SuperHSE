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
    if (socket.connect(serverIp, serverPort) != sf::Socket::Done){
        throw connectionException(serverIp.toString()+ ":" + std::to_string(serverPort));
    }
    std::string message = "Hello from the client!\n";
    socket.setBlocking(false);
    sf::Packet packet;
    packet << message;
    if (socket.send(packet) != sf::Socket::Done){
        throw sendingException();
    }
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
    sendPacket << (char *)&query_;
    socket.send(sendPacket);
    if (socket.receive(getPacket) == sf::Socket::Done){
        char get_buf[getPacket.getDataSize()];
        getPacket >> get_buf;
        answer answer_;
        std::memcpy(&answer_, get_buf, sizeof(answer));
        return answer_;
    }else {
        throw 1;
    }
}

void client::get(){

}

}

#endif
