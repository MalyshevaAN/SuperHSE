#ifndef ENEMY_CPP_
#define ENEMY_CPP_

#include "enemy.hpp"
#include "hse_utils.hpp"

namespace super_hse{
enemy::enemy(float x_, float y_):posX(x_), posY(y_){
};

void enemy::init(){
    enemy::buffer.loadFromFile("../assets/audio/enemy.wav");
    enemy::sound.setBuffer(buffer);
    get_texture_from_file("enemy_unactive.png", enemy::enemyUnactiveTexture);
    get_texture_from_file("enemy.png", enemy::enemyTexture);
    type = EntityType::ENEMY;
}

void enemy::disable(){
    setStatus(EntityStatus::DIEING);
    enemy::sound.play();
}

void enemy::change_pos(){
    if (pos_diff < 40){
        entity_sprite.move(0.5*path, 0);
        pos_diff+=0.2;
    }else{
        path*=-1;
        pos_diff = 0;
    }
}

void enemy::change(int frame){
    change_pos();
}

void enemy::disappear(){
    if (time_dissappearing < 5){
        entity_sprite.move(0,4);
        time_dissappearing += 0.1;
    }else{
        setStatus(EntityStatus::DEAD);
    }
}

void enemy::unable(){
    if (time_unable < 20){
        entity_sprite.setTexture(enemy::enemyUnactiveTexture);
        setStatus(EntityStatus::NOT_ACTIVE);
        time_unable += 0.1;
    }else {
        entity_sprite.setTexture(enemy::enemyTexture);
        time_unable = 0;
        setStatus(EntityStatus::ACTIVE);
    }
}
}

#endif
