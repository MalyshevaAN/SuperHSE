#ifndef MULTILEVEL_CPP
#define MULTILEVEL_CPP

#include "multiplayer_scene.hpp"


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
    nextPositionCollider.left += movement.x;
    nextPositionCollider.top += movement.y;
    const float dTimeSeconds = dTime.asSeconds();
    std::pair<bool , bool> collision = current_client.send(nextPositionCollider.left, nextPositionCollider.top, nextPositionCollider.width, nextPositionCollider.height, movement.x, movement.y);
        // bool isCollidingWithWall = false;
        // bool isCollidingWithFloor = false;
        // for (auto &entity : level.colliders) {
        //     sf::FloatRect intersect;
        //     if (nextPositionCollider.intersects(entity, intersect)) {
        //         // проверить тип объекта, с кем пересеклись (в данном случае -
        //         // стены/пол)
        //         // TODO - добавить проверку на тип объекта (тут нужна Настя и её
        //         // енамы)

        //         // проверка что пересекаемся с полом
        //         if (nextPositionCollider.top + nextPositionCollider.height >=
        //             entity.top) {
        //             isCollidingWithFloor = true;
        //             nextPositionCollider.top -= movement.y;
        //             movement.y = 0;

        //             // если после отката человечка наверх мы всё равно пересекаемся
        //             // с блоком - значит он стена
        //             if (nextPositionCollider.intersects(entity, intersect)) {
        //                 isCollidingWithWall = true;
        //             }
        //         } else {
        //             isCollidingWithWall = true;
        //         }
        //     }
        // }
    bool isCollidingWithWall = collision.first;
    bool isCollidingWithFloor = collision.second;
    if (isCollidingWithFloor){
        movement.y = 0;
    }
        //std::cerr << isCollidingWithWall << ' ' << isCollidingWithFloor << " 3\n";
    player1.isGrounded = isCollidingWithFloor;

    if (!isCollidingWithWall) {
        player1.move(movement.x, 0);
    }
    if (!isCollidingWithFloor) {
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
