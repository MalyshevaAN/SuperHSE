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

}  // namespace super_hse

