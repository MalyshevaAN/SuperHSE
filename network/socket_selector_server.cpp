#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <vector>
#include <memory>


int main(){
    std::cout << "Server Running" << std::endl;

    sf::TcpListener listener;
    sf::SocketSelector selector;
    bool done = false;
    std::vector<sf::TcpSocket *> clients;

    listener.listen(2000);
    selector.add(listener);
    while(!done){
        if (selector.wait()){
            if(selector.isReady(listener)){
                sf::TcpSocket *socket = new sf::TcpSocket;
                //sf::TcpSocket> socket = std::make_unique<sf::TcpSocket>();
                listener.accept(*socket);
                sf::Packet packet;
                std::string id;
                if(socket->receive(packet) == sf::Socket::Done){
                    packet >> id;
                }
                std::cout << id << " has been connected to the chat room" << std::endl;
                clients.push_back(socket);
                selector.add(*socket);
            }else{
                for (int i = 0; i < clients.size(); ++i){
                    if(selector.isReady(*clients[i])){
                        sf::Packet new_packet, sendPacket;
                        if (clients[i]->receive(new_packet) == sf::Socket::Done){
                            std::string text;
                            new_packet >> text;
                            std::cout << text << '\n';
                            sendPacket << text;
                            for (int j = 0; j < clients.size(); ++j){
                                if (i != j){
                                    clients[j]->send(sendPacket);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < clients.size(); ++i){
            delete clients[i];
    }
    return 0;
}
