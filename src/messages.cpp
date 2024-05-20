#ifndef MESSAGES_CPP
#define MESSAGES_CPP

#include "messages.hpp"

namespace super_hse{
void query::fill_query(sf::Packet &packet){
    packet << nextPositionColliderLeft << nextPositionColliderTop <<  nextPositionColliderWidth <<  nextPositionColliderHeight << movement_x << movement_y;
}

void query::get_query_from_packet(sf::Packet &packet){
    packet >> nextPositionColliderLeft >> nextPositionColliderTop >> nextPositionColliderWidth >> nextPositionColliderHeight >> movement_x >> movement_y;
}

void answer::fill_answer(sf::Packet &packet){
    packet << isCollidingWithWall << isCollidingWithFloor << movement_x << movement_y << lose_life << gathered_coin_index << killed_enemy_index << run_into_enemy_index;
}

void answer::get_answer_from_packet(sf::Packet &packet){
    packet >> isCollidingWithWall >> isCollidingWithFloor >> movement_x >> movement_y >> lose_life >> gathered_coin_index >> killed_enemy_index >> run_into_enemy_index;
}

}

#endif
