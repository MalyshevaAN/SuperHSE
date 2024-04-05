#include "game.hpp"
#include "sql.hpp"

int main() {
    super_hse::executeQuery();
    auto game = super_hse::Game();
    game.run();
    super_hse::closeDB();
    return 0;
}
