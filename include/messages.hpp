#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <SFML/Network.hpp>

namespace super_hse{

    
struct query{
    float nextPositionColliderLeft{};
    float nextPositionColliderTop{};
    float nextPositionColliderWidth{};
    float nextPositionColliderHeight{};
    float movement_x{};
    float movement_y{};

    void fill_query(sf::Packet &packet);
    void get_query_from_packet(sf::Packet &packet);
    // add info about current frame cause it is important for correct drawing for another client
};

struct answer{
    bool isCollidingWithWall{};
    bool isCollidingWithFloor{};
    float movement_x{};
    float movement_y{};
    bool lose_life = false;
    int gathered_coin_index = -1;
    int killed_enemy_index = -1;
    int run_into_enemy_index = -1;

    void fill_answer(sf::Packet &packet);
    void get_answer_from_packet(sf::Packet &packet);

    // add information about enemies, coins, states
};


}

#endif
