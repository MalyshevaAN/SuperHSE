#include <cassert>
#include <string>
#include <vector>
#include "game.hpp"
#include "sql.hpp"

namespace super_hse {

void test_getSkinPath() {
    std::vector<std::string> expected = {
        "ivankalinin.png", "khrabrov.png", "antipov.png", "annaglag.png",
        "egor2.png",       "kopel.png",    "hse.png",     "red.png",
        "blue.png",        "white.png",    "purple.png"
    };
    for (int i = 1; i <= 11; ++i) {
        assert(super_hse::getSkinPath(i) == expected[i - 1]);
    }
}

void test_getSkinCost() {
    std::vector<int> expected = {0, 10, 10, 10, 10, 10, 40, 40, 0, 0, 0};
    for (int i = 1; i <= 11; ++i) {
        assert(super_hse::getSkinCost(i) == expected[i - 1]);
    }
}

}  // namespace super_hse

int main() {
    super_hse::executeQuery();

    super_hse::test_getSkinPath();
    super_hse::test_getSkinCost();
    auto game = super_hse::Game();
    bool success = false;
    int i = 0;
    while (!success) {
        success = game.registerUser("user" + std::to_string(i), "password");
        ++i;
    }
    int id = super_hse::loginUser("user" + std::to_string(i - 1), "password");
    assert(id != -1);

    assert(super_hse::getUsername(id) == "user" + std::to_string(i - 1));
    assert(super_hse::getBalance(id) == 0);
    assert(super_hse::getCurrentSkin(id) == "ivankalinin.png");
    assert(super_hse::getCurrentSkinNum(id) == 1);

    assert(super_hse::isLevelAvailable(id, 1) == true);
    for (int i = 2; i <= super_hse::Game::levelsCount; ++i) {
        assert(super_hse::isLevelAvailable(id, i) == false);
    }

    assert(super_hse::getBalance(id) == 0);

    super_hse::closeDB();
    return 0;
}