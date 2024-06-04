#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <vector>
#include <LDtkLoader/Project.hpp>
#include "level_entities.hpp"
#include <mutex>


namespace super_hse{

enum class SERVER_STATE{
    WAIT_FOR_FIRST_CONNECTION,
    WAIT_FOR_SECOND_CONNECTION,
    CONNECTED
};

struct player_info{
    float x;
    float y;
    int gathered_coin_id = -1;
    int killed_enemy_id = -1;
    int skin_id = 0;
    int skin_col = 0;
    int skin_row = 11;
};

class server {
    sf::IpAddress serverIp;
    int serverPort1;
    int serverPort2;
    sf::TcpListener listener1;
    sf::TcpListener listener2;
    sf::TcpSocket socket1;
    sf::TcpSocket socket2;
    std::vector<player_info> players;
    player_info player1;
    player_info player2;
    SERVER_STATE state = SERVER_STATE::WAIT_FOR_FIRST_CONNECTION;
    level_entities entities;
    std::mutex m;
    bool game_started = false;

    void update_player_state_and_send(query &query_, answer &answer_, sf::FloatRect &nextPositionCollider, int index);
public:
    server();
    void run();
    void waitForConnection(int player);
    static void updateSceneWrapper(server* serverObj, int num);
    void updateScene(int num);
};
}

#endif
