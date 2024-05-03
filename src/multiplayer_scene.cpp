#ifndef MULTILEVEL_CPP
#define MULTILEVEL_CPP

#include "multiplayer_scene.hpp"


namespace super_hse{
MultiLevelScene::MultiLevelScene(const std::string &serverIp_, const int serverPort_){
    current_client.init(serverIp_, serverPort_); // в будущем данные, введенные польлзователем
}

MultiLevelScene::MultiLevelScene(std::string ldtk_filename){

}

void MultiLevelScene::update(sf::Time &dTime){

}

void MultiLevelScene::draw(sf::RenderWindow &window){
    
}

void MultiLevelScene::handleInput(sf::Event &event){
    
}

void MultiLevelScene::updateSceneSize(){
    
}

}

#endif
