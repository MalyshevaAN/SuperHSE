#include "hse_utils.hpp"
#include <filesystem>
#include <iostream>
#include "game.hpp"
#include "sql.hpp"

namespace super_hse {

bool is_level_available(int num) {
    return isLevelAvailable(Game::player_id, num);
}
}  // namespace super_hse
