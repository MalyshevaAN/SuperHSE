#include "game.hpp"
#include "sql.hpp"
#include <SFML/Network.hpp>

int main() {
    sf::TcpSocket socket;
    sf::IpAddress serverIp("127.0.0.1");
    unsigned short serverPort = 8000;

    if (socket.connect(serverIp, serverPort) != sf::Socket::Done){
        std::cerr << "Failed to connect to server." << std::endl;
        return -1;
    }

    std::string message = "Hello from the client!\n";
    sf::Packet packet;
    packet << message;
    if (socket.send(packet) != sf::Socket::Done){
        std::cerr << "Failed to send data to server." << std::endl;
        return -1;
    }

    std::cout << "Data sent to server\n";
    super_hse::executeQuery();
    auto game = super_hse::Game();
    game.run();
    super_hse::closeDB();
    return 0;
}
