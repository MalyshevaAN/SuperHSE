#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <SFML/Network.hpp>
#include <map>
#include <string>

namespace super_hse {

static std::map<std::string, int> game_state = {
    {"playing" , 1}, 
    {"lose" , 2}, 
    {"win", 3}
};

struct query {
    int state = game_state["playing"];
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

struct answer {
    int partner_state = game_state["playing"];
    bool isCollidingWithWall{};
    bool isCollidingWithFloor{};
    float movement_x{};
    float movement_y{};
    float x_partner{};
    float y_partner{};
    int skin_id_partner = 0;
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

}  // namespace super_hse

#endif
