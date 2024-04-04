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
    get_texture_from_file("enemy_unactive.png", enemy::enemyUnactiveTexture);
    get_texture_from_file("enemy.png", enemy::enemyTexture);
}

void enemy::disable(){
    state = EnemyState::dieing;
    enemy::sound.play();
}

void enemy::change_pos(){
    if (pos_diff < 40){
        enemySprite.move(0.5*path, 0);
        pos_diff+=0.2;
    }else{
        path*=-1;
        pos_diff = 0;
    }
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
    if (time_unable < 20){
        enemySprite.setTexture(enemy::enemyUnactiveTexture);
        state = EnemyState::not_active;
        time_unable += 0.1;
    }else {
        enemySprite.setTexture(enemy::enemyTexture);
        time_unable = 0;
        state = EnemyState::active;
    }
}
}

#endif
