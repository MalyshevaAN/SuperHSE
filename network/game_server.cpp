#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <vector>

int main(){
    std::cout<<"Server is listening on port 8000\n";
    sf::IpAddress serverIp = sf::IpAddress("127.0.0.1");
    int serverPort = 8000;
    sf::TcpSocket socket;


    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::vector<sf::TcpSocket *> clients;
    listener.listen(serverPort);
    selector.add(listener);
    bool done = false;
    while(!done){
        if (selector.wait()){
            if(selector.isReady(listener)){
                sf::TcpSocket *socket = new sf::TcpSocket;
                listener.accept(*socket);
                std::cout << "Get new client!\n";
                clients.push_back(socket);
                selector.add(*socket);
            }else{
                for (int i = 0; i < clients.size(); ++i){
                    if (selector.isReady(*clients[i])){
                        sf::Packet get_packet, send_packet;
                        if (clients[i]->receive(get_packet) == sf::Socket::Done){
                            std::string mode;
                            get_packet >> mode;
                            if (mode == "q"){
                                sf::Int32 size = clients.size();
                                send_packet << size;
                                clients[i]->send(send_packet);
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
