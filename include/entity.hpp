#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace super_hse{

    enum class EntityStatus {
        ACTIVE, 
        NOT_ACTIVE, 
        DIEING,
        DEAD
    };

    struct entity {
        sf::Sprite entity_sprite;
        virtual void disable() = 0;
        virtual void disappear() = 0;
        virtual void change(int frame) = 0;
        virtual void unable() = 0;
        virtual void setStatus(EntityStatus status_);
        virtual EntityStatus getStatus();

    protected:
        EntityStatus status = EntityStatus::ACTIVE;
    };
}
#endif
