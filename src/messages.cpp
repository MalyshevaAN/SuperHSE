#ifndef MESSAGES_CPP
#define MESSAGES_CPP

#include "messages.hpp"
#include <SFML/Network.hpp>

namespace super_hse {

void query::fill_query(sf::Packet &packet) {
    packet << state << nextPositionColliderLeft << nextPositionColliderTop
           << nextPositionColliderWidth << nextPositionColliderHeight
           << movement_x << movement_y << skin_id << skin_col << skin_row;
}

void query::get_query_from_packet(sf::Packet &packet) {
    packet >> state >> nextPositionColliderLeft >> nextPositionColliderTop >>
        nextPositionColliderWidth >> nextPositionColliderHeight >> movement_x >>
        movement_y >> skin_id >> skin_col >> skin_row;
}

void answer::fill_answer(sf::Packet &packet) {
    packet << partner_state << isCollidingWithWall << isCollidingWithFloor << movement_x
           << movement_y << x_partner << y_partner << skin_id_partner
           << skin_col_partner << skin_row_partner << lose_life
           << gathered_coin_index << killed_enemy_index << run_into_enemy_index
           << gathered_coin_index_partner << killed_enemy_index_partner;
}

void answer::get_answer_from_packet(sf::Packet &packet) {
    packet >> partner_state >> isCollidingWithWall >> isCollidingWithFloor >> movement_x >>
        movement_y >> x_partner >> y_partner >> skin_id_partner >>
        skin_col_partner >> skin_row_partner >> lose_life >>
        gathered_coin_index >> killed_enemy_index >> run_into_enemy_index >>
        gathered_coin_index_partner >> killed_enemy_index_partner;
}

}  // namespace super_hse

#endif
