#ifndef SQL_HPP_
#define SQL_HPP_

#include <string>

namespace super_hse {
void executeQuery();

void closeDB();

[[nodiscard]] std::string getUsername(int id);

[[nodiscard]] int getBalance(int id);

void updateBalance(int id, int newBalance);

bool registerUser(const std::string &username, const std::string &password);

[[nodiscard]] int
loginUser(const std::string &username, const std::string &password);

[[nodiscard]] std::string getCurrentSkin(int id);

[[nodiscard]] bool isLevelAvailable(int id, int level);

void updateLevel(int id, int level, int newTime, int newCash);

void addLevelsForUser(int id, int levelsCount);

[[nodiscard]] std::string updateSkin(int id, int newSkin);

}  // namespace super_hse

#endif  // SQL_HPP_