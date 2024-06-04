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
    int skin_id{};
    int skin_col{};
    int skin_row{};

    void fill_query(sf::Packet &packet);
    void get_query_from_packet(sf::Packet &packet);
};

struct answer{
    bool isCollidingWithWall{};
    bool isCollidingWithFloor{};
    float movement_x{};
    float movement_y{};
    float x_partner{};
    float y_partner{};
    int skin_id_partner=0;
    int skin_col_partner{};
    int skin_row_partner{};
    bool lose_life = false;
    bool lose_life_partner = false;
    int gathered_coin_index = -1;
    int killed_enemy_index = -1;
    int run_into_enemy_index = -1;
    int gathered_coin_index_partner = -1;
    int killed_enemy_index_partner = -1;

    void fill_answer(sf::Packet &packet);
    void get_answer_from_packet(sf::Packet &packet);

    // add information about enemies, coins, states
};


}

#endif
