#ifndef SQL_HPP_
#define SQL_HPP_

#include <string>

namespace super_hse {

struct LvlRecords {
    int lives;
    int coins;
};

void executeQuery();

void closeDB();

[[nodiscard]] std::string getUsername(int id);

[[nodiscard]] int getBalance(int id);

void updateBalance(int id, int newBalance);

bool registerUser(const std::string &username, const std::string &password);

[[nodiscard]] int
loginUser(const std::string &username, const std::string &password);

[[nodiscard]] std::string getCurrentSkin(int id);

[[nodiscard]] int getCurrentSkinNum(int id);

[[nodiscard]] bool isLevelAvailable(int id, int level);

void updateLevel(int id, int level, int newLives, int newCoins);

// void addLevelsForUser(int id, int levelsCount);

void updateSkin(int id, int newSkin);

[[nodiscard]] bool isSkinAvailable(int id, int skin);

[[nodiscard]] int getSkinCost(int skin);

void buySkin(int id, int skin);

LvlRecords getLevelRecords(int id, int level);

}  // namespace super_hse

#endif  // SQL_HPP_