#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <vector>

namespace super_hse{

enum class SERVER_STATE{
    WAIT_FOR_CONNECTION,
    CONNECTED
};

class server {
    sf::IpAddress serverIp;
    int serverPort;
    sf::TcpListener listener;
    sf::TcpSocket socket;
    SERVER_STATE state = SERVER_STATE::WAIT_FOR_CONNECTION;

public:
    server();
    void run();
    void waitForConnection();
    void updateScene();
};
}

#endif
