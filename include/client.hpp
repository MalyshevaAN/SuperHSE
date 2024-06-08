#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include <string>
#include "hse_utils.hpp"
#include "messages.hpp"

namespace super_hse {
enum class CONNECTION_STATE {
    IS_NOT_CONNECTED,
    WAITING_FOR_PARTNER,
    DISCONNECTED,
    READY_TO_PLAY
};

class client {
    sf::IpAddress serverIp;
    unsigned int serverPort;
    sf::TcpSocket socket;

public:
    client() = default;
    void init(const std::string &server_ip_, const unsigned int server_port_);
    CONNECTION_STATE state;

    // CONNECTION_STATE get_connection_state();
    void check();
    answer send(query &query_);
    void get();
};
}  // namespace super_hse

#endif
