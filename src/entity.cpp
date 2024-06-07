#ifndef ENTITY_CPP
#define ENTITY_CPP
#include "entity.hpp"

namespace super_hse {
void entity::setStatus(EntityStatus status_) {
    status = status_;
}

EntityStatus entity::getStatus() {
    return status;
}

}  // namespace super_hse

#endif
