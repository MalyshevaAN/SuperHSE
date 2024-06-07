#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace super_hse {

enum class EntityStatus { ACTIVE, NOT_ACTIVE, DIEING, DEAD };

enum class EntityType {
    COIN,
    ENEMY,
};

struct entity {
    sf::Sprite entity_sprite;
    virtual void disable() = 0;
    virtual void disappear() = 0;
    virtual void change(int frame) = 0;
    virtual void unable() = 0;
    virtual void setStatus(EntityStatus status_);
    virtual EntityStatus getStatus();
    virtual EntityType getType() = 0;

protected:
    EntityStatus status = EntityStatus::ACTIVE;
};
}  // namespace super_hse
#endif
