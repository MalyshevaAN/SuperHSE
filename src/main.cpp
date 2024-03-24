#include "game.hpp"
#include "sql.hpp"

int main() {
    executeQuery();
    auto game = super_hse::Game();
    game.run();
    closeDB();
    return 0;
}
