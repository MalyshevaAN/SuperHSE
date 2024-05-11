#ifndef MULTILEVEL_CPP
#define MULTILEVEL_CPP

#include "multiplayer_scene.hpp"
#include "messages.hpp"


namespace super_hse{
MultiLevelScene::MultiLevelScene(const std::string &serverIp_, const int serverPort_, const int level_number_){
    current_client.init(serverIp_, serverPort_); // в будущем данные, введенные польлзователем
    try{
        std::filesystem::path p(std::filesystem::current_path());
        std::string filename = p.parent_path().string() + storage.at(level_number_);
        info = LevelInfo(filename);
        level.ldtk_filename = info.filename;
        level.project.loadFromFile(info.filename);
        level.init(
            info.tileLayerName,
            info.entityLayerName,
            info.colliderName,
            level_number_
        );
    }catch (std::out_of_range &e){
        throw noSuchLevel(std::to_string(level_number_));
    }
}

void MultiLevelScene::handleInput(sf::Event &event){
    
}

void MultiLevelScene::update(sf::Time &dTime){
    level.update(dTime, player1.get_position(), player1.get_active_lives());
    player1.update(dTime);
    sf::FloatRect nextPositionCollider = player1.getCollider();
    sf::Vector2f movement = player1.calcMovement(dTime);
    if (player1.isGrounded && movement.y > 0){
        movement.y = 0;
    }
    nextPositionCollider.left += movement.x;
    nextPositionCollider.top += movement.y;
    const float dTimeSeconds = dTime.asSeconds();
    query query_({nextPositionCollider.left, nextPositionCollider.top, nextPositionCollider.width, nextPositionCollider.height, movement.x, movement.y});
    answer answer_ = current_client.send(query_);
    if (answer_.lose_life){
        player1.lose_life();
    }

    if (answer_.gathered_coin_index != -1){
        level.entities.coins[answer_.gathered_coin_index].disable();
    }

    if (answer_.run_into_enemy_index != -1){
        level.entities.enemies[answer_.run_into_enemy_index].unable();
    }

    if (answer_.run_into_enemy_index != -1){
        level.entities.enemies[answer_.run_into_enemy_index].disable();
    }

    if (answer_.isCollidingWithFloor){
        movement.y = 0;
    }
        //std::cerr << isCollidingWithWall << ' ' << isCollidingWithFloor << " 3\n";
    player1.isGrounded = answer_.isCollidingWithFloor;

    if (!answer_.isCollidingWithWall) {
        player1.move(movement.x, 0);
    }
    if (!answer_.isCollidingWithFloor) {
        player1.move(0, movement.y);
    }
}

void MultiLevelScene::draw(sf::RenderWindow &window){
    window.clear(windowFillColor);
    level.render(window, info.tileLayerName);
    player1.draw(window);
    window.display();
}


void MultiLevelScene::updateSceneSize(){
    
}

}

#endif
