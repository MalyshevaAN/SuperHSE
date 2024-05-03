#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include "hse_utils.hpp"
#include <string>

namespace super_hse{
    class client {
        sf::IpAddress serverIp;
        unsigned int serverPort;
        sf::TcpSocket socket;
    public:
        client() = default;
        void init(const std::string &server_ip_, const unsigned int server_port_);

        void send();
        void get();
    };
}

#endif
