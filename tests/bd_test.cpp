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
        assert(getSkinPath(i) == expected[i - 1]);
    }
}

void test_getSkinCost() {
    std::vector<int> expected = {0, 10, 10, 10, 10, 10, 40, 40, 0, 0, 0};
    for (int i = 1; i <= 11; ++i) {
        assert(getSkinCost(i) == expected[i - 1]);
    }
}

void test_bd() {
    executeQuery();

    test_getSkinPath();
    test_getSkinCost();
    auto game = Game();
    bool success = false;
    int num = 0;
    while (!success) {
        ++num;
        success = registerUser("marichka" + std::to_string(num), "password");
    }
    int id = loginUser("marichka" + std::to_string(num), "password");
    assert(id != -1);

    assert(getUsername(id) == "marichka" + std::to_string(num));
    assert(getBalance(id) == 0);
    assert(getCurrentSkin(id) == "ivankalinin.png");
    assert(getCurrentSkinNum(id) == 1);

    assert(isLevelAvailable(id, 1) == true);
    for (int i = 2; i <= Game::levelsCount; ++i) {
        assert(isLevelAvailable(id, i) == false);
    }

    assert(getBalance(id) == 0);

    updateBalance(id, 1703);
    assert(getBalance(id) == 1703);

    buySkin(id, 2);
    assert(getCurrentSkin(id) == "khrabrov.png");
    assert(getCurrentSkinNum(id) == 2);
    assert(getBalance(id) == 1703 - getSkinCost(2));

    updateSkin(id, 3);  // skin 3 is not available, should not change
    assert(getCurrentSkinNum(id) == 2);

    updateSkin(id, -228);  // incorrect skinId, should not change
    assert(getCurrentSkinNum(id) == 2);

    updateSkin(id, 52);  // incorrect skinId, should not change
    assert(getCurrentSkinNum(id) == 2);

    updateLevel(id, 1, 3, 52);
    auto records = getLevelRecords(id, 1);
    assert(records.lives == 3);
    assert(records.coins == 52);
    assert(isLevelAvailable(id, 2) == true);

    updateLevel(id, 1, 2, 52);
    records = getLevelRecords(id, 1);
    assert(records.lives == 3);
    assert(records.coins == 52);

    success = registerUser("marichka" + std::to_string(num), "legitCHECK");
    assert(success == false);

    closeDB();
}
}  // namespace super_hse
