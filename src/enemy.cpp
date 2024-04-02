#ifndef ENEMY_CPP_
#define ENEMY_CPP_

#include "enemy.hpp"
#include "hse_utils.hpp"

namespace super_hse{
enemy::enemy(float x_, float y_):posX(x_), posY(y_){};
EnemyState enemy::get_state(){
    return state;
}

void enemy::init(){
    enemy::buffer.loadFromFile("../assets/audio/enemy.wav");
    enemy::sound.setBuffer(buffer);
}

void enemy::disable(){
    state = EnemyState::dieing;
    enemy::sound.play();
}

void enemy::disappear(){
    if (time_dissappearing < 5){
        enemySprite.move(0,4);
        time_dissappearing += 0.1;
    }else{
        state = EnemyState::dead;
    }
}

void enemy::unable(){
    if (time_unable < 10){
        state = EnemyState::not_active;
        time_unable += 0.1;
    }else {
        time_unable = 0;
        state = EnemyState::active;
    }
}
}

#endif
