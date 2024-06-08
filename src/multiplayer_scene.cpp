#ifndef MULTILEVEL_CPP
#define MULTILEVEL_CPP

#include "multiplayer_scene.hpp"
#include "game.hpp"
#include "main_menu_scene.hpp"
#include "messages.hpp"
#include "lose_scene.hpp"
#include "win_scene.hpp"

namespace super_hse {
MultiLevelScene::MultiLevelScene(
    const std::string &serverIp_,
    const int serverPort_,
    const int level_number_
) {
    current_client.init(
        serverIp_, serverPort_
    );  // в будущем данные, введенные польлзователем
    try {
        std::filesystem::path p(std::filesystem::current_path());
        std::string filename =
            p.parent_path().string() + storage.at(level_number_);
        info = LevelInfo(filename);
        level.ldtk_filename = info.filename;
        level.project.loadFromFile(info.filename);
        level.init(
            info.tileLayerName, info.entityLayerName, info.colliderName,
            level_number_+5
        );
    } catch (std::out_of_range &e) {
        throw noSuchLevel(std::to_string(level_number_));
    }
    get_texture_from_file("waiting_for_connection.png", waitForPartnerTexture);
    waitForPartner.setTexture(waitForPartnerTexture);
    waitForPartner.setPosition(Game::windowWidth / 8, Game::windowHeight / 2);
    waitForPartner.setScale(0.5, 0.5);
    get_texture_from_file(
        "server_is_unavailable.png", serverIsUnavailableTexture
    );
    serverIsUnavailable.setTexture(serverIsUnavailableTexture);
    serverIsUnavailable.setPosition(
        Game::windowWidth / 6, Game::windowHeight / 2
    );
    serverIsUnavailable.setScale(0.5, 0.5);
}

void MultiLevelScene::handleInput(sf::Event &event) {
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

void MultiLevelScene::update(sf::Time &dTime) {
    if (current_client.state == CONNECTION_STATE::READY_TO_PLAY) {
        level.update(dTime, player.get_position(), player.get_active_lives());
        player.update(dTime);
        sf::FloatRect nextPositionCollider = player.getCollider();
        sf::Vector2f movement = player.calcMovement(dTime);
        nextPositionCollider.left += movement.x;
        nextPositionCollider.top += movement.y;
        query query_(
            {game_state["playing"], nextPositionCollider.left, nextPositionCollider.top,
             nextPositionCollider.width, nextPositionCollider.height,
             movement.x, movement.y, player.getCurrentSkinId(),
             player.getCurrentFrameColumn(), player.getCurrentFrameRow()}
        );
        if (player.get_active_lives() == 0){
            query_.state = game_state["lose"];
            answer answer_ = current_client.send(query_);
            SceneManager::changeScene(std::make_unique<LoseScene>('m', 0));
            return;
        }

        if (player.get_position().x >= level.tilemap.width - 60){
            int gatherCoins = level.get_gathered_coins();
            query_.state = game_state["win"];
            answer answer_ = current_client.send(query_);
            SceneManager::changeScene(std::make_unique<WinScene>(gatherCoins, level.level_number + 1, player.get_active_lives(), 'm'));
            return;
        }
        answer answer_ = current_client.send(query_);
        if (current_client.state == CONNECTION_STATE::READY_TO_PLAY) {
            if (answer_.partner_state == game_state["lose"]){
                SceneManager::changeScene(std::make_unique<LoseScene>('m', 0));
                return;
            }
            partner.update(
                answer_.x_partner, answer_.y_partner, answer_.skin_id_partner,
                answer_.skin_col_partner, answer_.skin_row_partner
            );
            partner.changePos();
            player.isGrounded = answer_.isCollidingWithFloor;
            if (!answer_.isCollidingWithWall) {
                player.move(answer_.movement_x, 0);
            }
            if (!answer_.isCollidingWithFloor) {
                player.move(0, answer_.movement_y);
            }
            if (answer_.gathered_coin_index != -1) {
                level.entities.coins[answer_.gathered_coin_index].disable();
            }
            if (answer_.gathered_coin_index_partner != -1) {
                level.entities.coins[answer_.gathered_coin_index_partner]
                    .disable();
            }
            if (answer_.killed_enemy_index != -1) {
                level.entities.enemies[answer_.killed_enemy_index].disable();
            }
            if (answer_.killed_enemy_index_partner != -1) {
                level.entities.enemies[answer_.killed_enemy_index_partner]
                    .disable();
            }
            if (answer_.run_into_enemy_index != -1) {
                level.entities.enemies[answer_.run_into_enemy_index].unable();
            }
            if (answer_.lose_life) {
                player.lose_life();
            }
        }
    }
}

void MultiLevelScene::draw(sf::RenderWindow &window) {
    if (current_client.state == CONNECTION_STATE::READY_TO_PLAY) {
        window.clear(windowFillColorPlay);
        level.render(window, info.tileLayerName);
        player.draw(window);
        partner.draw(window);
    } else if (current_client.state == CONNECTION_STATE::IS_NOT_CONNECTED) {
        sf::View view;
        view.setSize(Game::windowWidth, Game::windowHeight);
        view.setCenter(Game::windowWidth / 2, Game::windowHeight / 2);
        window.clear(windowFillColorWait);
        window.setView(view);
        window.draw(Game::backButton);
        window.draw(serverIsUnavailable);
    } else if (current_client.state == CONNECTION_STATE::WAITING_FOR_PARTNER) {
        window.clear(windowFillColorWait);
        current_client.check();
        window.draw(waitForPartner);
    }
    window.display();
}

void MultiLevelScene::updateSceneSize() {
}

}  // namespace super_hse

#endif
