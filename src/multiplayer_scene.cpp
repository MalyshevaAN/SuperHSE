#ifndef MULTILEVEL_CPP
#define MULTILEVEL_CPP

#include "multiplayer_scene.hpp"
#include "messages.hpp"
#include "game.hpp"
#include "main_menu_scene.hpp"


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
    get_texture_from_file("waiting_for_connection.png", waitForPartnerTexture);
    waitForPartner.setTexture(waitForPartnerTexture);
    waitForPartner.setPosition(Game::windowWidth / 8, Game::windowHeight / 2);
    waitForPartner.setScale(0.5, 0.5);
}

void MultiLevelScene::handleInput(sf::Event &event){
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (Game::backButton.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y
                )) {
                SceneManager::changeScene(std::make_unique<MainMenuScene>());
                return;
            }
        }
    }
}

void MultiLevelScene::update(sf::Time &dTime){
    if (current_client.state == CONNECTION_STATE::READY_TO_PLAY){
        level.update(dTime, player1.get_position(), player1.get_active_lives());
        player1.update(dTime);
        sf::FloatRect nextPositionCollider = player1.getCollider();
        sf::Vector2f movement = player1.calcMovement(dTime);
        nextPositionCollider.left += movement.x;
        nextPositionCollider.top += movement.y;
        query query_({nextPositionCollider.left, nextPositionCollider.top, nextPositionCollider.width, nextPositionCollider.height, movement.x, movement.y});
        answer answer_ = current_client.send(query_);
        player1.isGrounded = answer_.isCollidingWithFloor;
        if(!answer_.isCollidingWithWall){
            player1.move(movement.x, 0);
        }
        if(!answer_.isCollidingWithFloor){
            player1.move(0, movement.y);
        }
        if(answer_.gathered_coin_index != -1){
            level.entities.coins[answer_.gathered_coin_index].disable();
        }
        if (answer_.killed_enemy_index != -1){
            level.entities.enemies[answer_.killed_enemy_index].disable();
        }
        if(answer_.run_into_enemy_index != -1){
            level.entities.enemies[answer_.run_into_enemy_index].unable();
        }
        if(answer_.lose_life){
            player1.lose_life();
        }
    }
}

void MultiLevelScene::draw(sf::RenderWindow &window){
    if (current_client.state == CONNECTION_STATE::READY_TO_PLAY){
        window.clear(windowFillColorPlay);
        level.render(window, info.tileLayerName);
        player1.draw(window);
    }else if (current_client.state == CONNECTION_STATE::IS_NOT_CONNECTED){
        window.clear(windowFillColorWait);
        window.draw(Game::backButton);
    }else if (current_client.state == CONNECTION_STATE::WAITING_FOR_PARTNER){
        window.clear(windowFillColorWait);
        current_client.check();
        window.draw(waitForPartner);
    }
    window.display();
}


void MultiLevelScene::updateSceneSize(){

}

}

#endif
