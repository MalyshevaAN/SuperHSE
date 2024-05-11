#ifndef MESSAGE_HPP
#define MESSAGE_HPP

namespace super_hse{


#pragma pack(push, 1)
    
struct query{
    float nextPositionColliderLeft{};
    float nextPositionColliderTop{};
    float nextPositionColliderWidth{};
    float nextPositionColliderHeight{};
    float movement_x{};
    float movement_y{};
    // add info about current frame cause it is important for correct drawing for another client
};

struct answer{
    bool isCollidingWithWall{};
    bool isCollidingWithFloor{};
    bool lose_life = false;
    int gathered_coin_index = -1;
    int killed_enemy_index = -1;
    int run_into_enemy_index = -1;

    // add information about enemies, coins, states
};

#pragma pack(pop)

}

#endif
