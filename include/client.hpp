#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include "hse_utils.hpp"
#include <string>

namespace super_hse{
    enum class CONNECTION_STATE {
        IS_NOT_CONNECTED,
        WAITING_FOR_PARTER,
        READY_TO_PLAY
    };

    class client {
        sf::IpAddress serverIp;
        unsigned int serverPort;
        sf::TcpSocket socket;
    public:
        client() = default;
        void init(const std::string &server_ip_, const unsigned int server_port_);


        CONNECTION_STATE get_connection_state();
        std::pair<bool, bool> send(int x, int y, int width, int height,int movement_x, int movement_y);
        void get();
    };
}

#endif
