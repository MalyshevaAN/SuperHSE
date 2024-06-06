#ifndef SERVER_CPP
#define SERVER_CPP

#include "server.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <thread>
#include "cstring"
#include "game.hpp"
#include "messages.hpp"
#include "scene.hpp"
#include "server_info_scene.hpp"

namespace super_hse {

std::pair<int, int> getPorts() {
    // вернуть свободные порты сервера или что-то такое
    return {8000, 8001};
}

server::server()
    : serverIp(sf::IpAddress::getLocalAddress()) {
    const std::pair<int, int> ports = getPorts();
    serverPort1 = ports.first;
    serverPort2 = ports.second;

    std::filesystem::path p(std::filesystem::current_path());
    entities.init(p.parent_path().string() + "/assets/files/multi_level.txt");
};

void server::waitForConnection(int player) {
    sf::Packet server_state;
    if (player == 1) {
        listener1.listen(serverPort1);
        listener1.accept(socket1);
        state = SERVER_STATE::WAIT_FOR_SECOND_CONNECTION;
        server_state << 1;
        socket1.send(server_state);
    }
    if (player == 2) {
        listener2.listen(serverPort2);
        listener2.accept(socket2);
        state = SERVER_STATE::CONNECTED;
        server_state << 2;
        socket1.send(server_state);
        socket2.send(server_state);
    }
    std::cerr << "Get new Client!\n";
}

void server::updateScene(int num) {
    sf::Packet getPacket;
    if (num == 1) {
        socket1.receive(getPacket);
        struct query query_;
        query_.get_query_from_packet(getPacket);
        std::memcpy(&query_, getPacket.getData(), sizeof(query));
        sf::FloatRect nextPositionCollider(
            query_.nextPositionColliderLeft, query_.nextPositionColliderTop,
            query_.nextPositionColliderWidth, query_.nextPositionColliderHeight
        );
        sf::Vector2f movement(query_.movement_x, query_.movement_y);
        for (auto elem : entities.enemies) {
            elem.change_pos();
        }
        answer answer_ = entities.update(nextPositionCollider, movement);
        sf::Packet sendPacket;
        answer_.fill_answer(sendPacket);
        socket1.send(sendPacket);
    } else if (num == 2) {
        socket2.receive(getPacket);
        struct query query_;
        query_.get_query_from_packet(getPacket);
        std::memcpy(&query_, getPacket.getData(), sizeof(query));
        sf::FloatRect nextPositionCollider(
            query_.nextPositionColliderLeft, query_.nextPositionColliderTop,
            query_.nextPositionColliderWidth, query_.nextPositionColliderHeight
        );
        sf::Vector2f movement(query_.movement_x, query_.movement_y);
        for (auto elem : entities.enemies) {
            elem.change_pos();
        }
        answer answer_ = entities.update(nextPositionCollider, movement);
        sf::Packet sendPacket;
        answer_.fill_answer(sendPacket);
        socket2.send(sendPacket);
    }
}

void server::updateSceneWrapper(server *serverObj, int num) {
    serverObj->updateScene(num);
}

void server::run() {
    std::thread windowLoopThread([&]() {
        serverInfoScene.init();
        // вообще цикл внутри run, но можно вынести его сюда 
        // чтобы было удобно обновлять доступность портов и передавать обновления
        serverInfoScene.run();
    });

    std::thread stateSwitchThread([&]() {
        switch (state) {
            case SERVER_STATE::WAIT_FOR_FIRST_CONNECTION:
                waitForConnection(1);
                break;
            case SERVER_STATE::WAIT_FOR_SECOND_CONNECTION:
                waitForConnection(2);
            case SERVER_STATE::CONNECTED:
                // updateScene();
                std::thread th1(updateSceneWrapper, this, 1);
                std::thread th2(updateSceneWrapper, this, 2);
                th1.join();
                th2.join();
        }
    });

    windowLoopThread.join();
    stateSwitchThread.join();
}

}  // namespace super_hse

#endif
