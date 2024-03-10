#ifndef SQL_HPP_
#define SQL_HPP_

#include <string>

namespace super_hse {
void executeQuery();

void closeDB();

[[nodiscard]] std::string getUsername(int id);

[[nodiscard]] int getBalance(int id);

void updateBalance(int id, int newBalance);

void addUser(const std::string &username);  // TODO: add password

[[nodiscard]] std::string getCurrentSkin(int id);

[[nodiscard]] bool isLevelAvailable(int id, int level);

void updateLevel(int id, int level, int newTime, int newCash);

void addLevelsForUser(int id, int levelsCount);

}  // namespace super_hse

#endif  // SQL_HPP_