#ifndef COIN_CPP_
#define COIN_CPP_

#include "coin.hpp"

namespace super_hse{

void coin::disable(){
    is_active = false;
}

bool coin::get_status(){
    return is_active;
}
}


#endif
