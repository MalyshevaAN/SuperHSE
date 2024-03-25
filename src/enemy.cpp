#ifndef ENEMY_CPP_
#define ENEMY_CPP_

#include "enemy.hpp"
#include "hse_utils.hpp"

namespace super_hse{
enemy::enemy(float x_, float y_):posX(x_), posY(y_){};
bool enemy::get_status(){
    return is_alive;
}
void enemy::change_status(){
    is_alive = false;
}

void enemy::die(){

}
}

#endif
