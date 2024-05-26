#ifndef ENEMY_HPP_
#define ENEMY_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "hse_utils.hpp"

namespace super_hse {

enum class EnemyState { active, not_active, dieing, dead };

struct enemy {
    sf::Sprite enemySprite;
    static inline sf::Texture enemyTexture;
    static inline sf::Texture enemyUnactiveTexture;
    float posX;
    float posY;

    enemy(float x_, float y_);
    EnemyState get_state();
    void disable();
    void change_pos();
    void unable();
    void disappear();
    static void init();
    static inline sf::SoundBuffer buffer;
    static inline sf::Sound sound;

private:
    EnemyState state = EnemyState::active;
    float time_unable = 0;
    float time_dissappearing = 0;
    float pos_diff;
    int path = 1;
};
}  // namespace super_hse

#endif
