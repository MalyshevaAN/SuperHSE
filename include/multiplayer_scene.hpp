#ifndef MULTILEVEL_SCENE_HPP_
#define MULTILEVEL_SCENE_HPP_

#include "scene.hpp"
#include "client.hpp"
#include <map>

namespace super_hse {

class MultiLevelScene : public Scene {
private:
    std::string ldtk_filename;
    Player player1;
    Player player2;
    LevelInfo info;
    Level level; 
    client current_client{};

    const sf::Color windowFillColor = sf::Color(125, 166, 218);

    static inline std::map<int, std::string> storage = {
        {1, "/assets/files/multi_level.txt"}
    };

public:
    MultiLevelScene() = default;
    MultiLevelScene(const std::string &serverIp_, const int serverPort_, const int level_number_);
    void update(sf::Time &dTime) override;
    void draw(sf::RenderWindow &window) override;
    void handleInput(sf::Event &event) override;
    void updateSceneSize() override;
};

}  // namespace super_hse

#endif  // LEVEL_SCENE_HPP_
