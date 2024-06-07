#ifndef SERVER_HPP
#define SERVER_HPP

#include <LDtkLoader/Project.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "level_entities.hpp"
#include "server_info_scene.hpp"

namespace super_hse {

std::pair<int, int> getPorts();

enum class SERVER_STATE {
    WAIT_FOR_FIRST_CONNECTION,
    WAIT_FOR_SECOND_CONNECTION,
    CONNECTED
};

class server {
    sf::IpAddress serverIp;
    int serverPort1;
    int serverPort2;
    sf::TcpListener listener1;
    sf::TcpListener listener2;
    sf::TcpSocket socket1;
    sf::TcpSocket socket2;
    SERVER_STATE state = SERVER_STATE::WAIT_FOR_FIRST_CONNECTION;
    level_entities entities;

    ServerInfoScene serverInfoScene;

public:
    server();
    void run();
    void waitForConnection(int player);
    static void updateSceneWrapper(server *serverObj, int num);
    void updateScene(int num);
};
}  // namespace super_hse

#endif
