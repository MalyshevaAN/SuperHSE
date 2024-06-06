#ifndef SERVER_HPP
#define SERVER_HPP

#include <LDtkLoader/Project.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>
#include "level_entities.hpp"

namespace super_hse {

enum class SERVER_STATE {
    WAIT_FOR_FIRST_CONNECTION,
    WAIT_FOR_SECOND_CONNECTION,
    CONNECTED
};

struct Port {
    int number;
    bool is_available;
};

struct player_info {
    float x;
    float y;
    int gathered_coin_id = -1;
    int killed_enemy_id = -1;
    int skin_id = 0;
    int skin_col = 0;
    int skin_row = 11;
    int socket_number = 0;
};

class server {
    sf::IpAddress serverIp;
    std::vector<Port> ports;
    sf::TcpListener listener1;
    sf::TcpListener listener2;
    sf::TcpSocket socket1;
    sf::TcpSocket socket2;
    std::vector<player_info> players;
    SERVER_STATE state = SERVER_STATE::WAIT_FOR_FIRST_CONNECTION;
    level_entities entities;
    std::mutex m;
    bool game_started = false;

    void update_player_state_and_send(
        query &query_,
        answer &answer_,
        sf::FloatRect &nextPositionCollider,
        int index
    );

public:
    server();
    void run();
    void waitForConnection(int player);
    static void updateSceneWrapper(server *serverObj, int num);
    void updateScene(int num);
};
}  // namespace super_hse

#endif
