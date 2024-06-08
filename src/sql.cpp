#include "sql.hpp"
#include <sqlite3.h>
#include <fstream>
#include <iostream>
#include <string>
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/osrng.h"
#include "cryptopp/sha.h"
#include "game.hpp"

namespace super_hse {
sqlite3 *db;

std::string generateSalt() {
    CryptoPP::SecByteBlock salt(32);
    CryptoPP::OS_GenerateRandomBlock(false, salt, salt.size());
    CryptoPP::HexEncoder encoder;
    std::string hexSalt;
    encoder.Attach(new CryptoPP::StringSink(hexSalt));
    encoder.Put(salt, salt.size());
    encoder.MessageEnd();
    return hexSalt;
}

std::string hashPassword(const std::string &password, const std::string &salt) {
    std::string saltedPassword = password + salt;
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(
        digest, (CryptoPP::byte *)saltedPassword.c_str(),
        saltedPassword.length()
    );
    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
    return output;
}

void executeQuery() {
    char *err = 0;
    int rc = sqlite3_open("SuperHSE.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << '\n';
        sqlite3_close(db);
        return;
    }
    std::ifstream sqlFile("../sqlQuery.sql");
    std::string sqlQueries(
        (std::istreambuf_iterator<char>(sqlFile)),
        std::istreambuf_iterator<char>()
    );
    rc = sqlite3_exec(db, sqlQueries.c_str(), 0, 0, &err);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err << '\n';
        sqlite3_free(err);
    }
}

void closeDB() {
    sqlite3_close(db);
}

// maybe TODO getters in one func returning std::string

std::string getUsername(int id) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT USERNAME FROM USERS WHERE USER_ID = " + std::to_string(id);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    const char *usernameText =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    std::string username = usernameText ? usernameText : "";
    sqlite3_finalize(stmt);
    return username;
}

int getBalance(int id) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT BALANCE FROM USERS WHERE USER_ID = " + std::to_string(id);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    int balance = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return balance;
}

void updateBalance(int id, int newBalance) {
    std::string sql =
        "UPDATE USERS SET BALANCE = " + std::to_string(newBalance) +
        " WHERE USER_ID = " + std::to_string(id);
    char *err = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (rc != SQLITE_OK) {
        std::cerr << "Update balance error: " << err << '\n';
        sqlite3_free(err);
    }
}

bool registerUser(const std::string &username, const std::string &password) {
    if (username.empty() || password.empty()) {
        return false;
    }

    // сheck if username already exists
    std::string checkSql =
        "SELECT COUNT(*) FROM USERS WHERE USERNAME = '" + username + "'";
    sqlite3_stmt *checkStmt;
    sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, NULL);
    sqlite3_step(checkStmt);
    int count = sqlite3_column_int(checkStmt, 0);
    sqlite3_finalize(checkStmt);
    if (count > 0) {
        // already exists
        return false;
    }

    // new user
    std::string salt = generateSalt();
    std::string hashedPassword = hashPassword(password, salt);
    std::string sql =
        "INSERT INTO USERS (USERNAME, SALT, HASHED_PASSWORD) VALUES ('" +
        username + "', '" + salt + "', '" + hashedPassword + "')";
    char *err = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (rc != SQLITE_OK) {
        std::cerr << "Add user error: " << err << '\n';
        sqlite3_free(err);
    }

    std::string idSql =
        "SELECT USER_ID FROM USERS WHERE USERNAME = '" + username + "'";
    sqlite3_stmt *idStmt;
    sqlite3_prepare_v2(db, idSql.c_str(), -1, &idStmt, NULL);
    sqlite3_step(idStmt);
    int id = sqlite3_column_int(idStmt, 0);
    sqlite3_finalize(idStmt);

    // levels for the new user
    for (int i = 1; i <= Game::levelsCount; ++i) {
        sql = "INSERT INTO LEVELS (USER_ID, LVL_NUM, STATUS) VALUES (" +
              std::to_string(id) + ", " + std::to_string(i) + ", " +
              (i == 1 ? "1" : "0") + ")";
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
        if (rc != SQLITE_OK) {
            std::cerr << "Add levels error: " << err << '\n';
            sqlite3_free(err);
        }
    }

    // skins for the new user
    for (int i = 1; i <= Game::skinsCount; ++i) {
        sql = "INSERT INTO SKINS (USER_ID, ITEM_ID, STATUS) VALUES (" +
              std::to_string(id) + ", " + std::to_string(i) + ", " +
              ((i == 1 || i >= 9 && i <= 11) ? "1" : "0") + ")";
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
        if (rc != SQLITE_OK) {
            std::cerr << "Add skins error: " << err << '\n';
            sqlite3_free(err);
        }
    }

    return true;
}

int loginUser(const std::string &username, const std::string &password) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT USER_ID, SALT, HASHED_PASSWORD FROM USERS WHERE USERNAME = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    int step = sqlite3_step(stmt);
    int id = -1;
    if (step == SQLITE_ROW) {
        std::string salt =
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string passwordHash =
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string hashedPassword = hashPassword(password, salt);
        if (hashedPassword == passwordHash) {
            id = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return id;
}

std::string getCurrentSkin(int id) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT CURRENT_SKIN FROM USERS WHERE USER_ID = " + std::to_string(id);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    const char *skinText =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    int skinId = std::stoi(skinText);
    sql = "SELECT PATH FROM ITEMS WHERE ITEM_ID = " + std::to_string(skinId);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    const char *pathText =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    std::string path = pathText ? pathText : "";
    sqlite3_finalize(stmt);
    return path;
}

int getCurrentSkinNum(int id) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT CURRENT_SKIN FROM USERS WHERE USER_ID = " + std::to_string(id);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    const char *skinText =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    int skinId = std::stoi(skinText);
    return skinId;
}

std::string getSkinPath(int skin_id) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT PATH FROM ITEMS WHERE ITEM_ID = " + std::to_string(skin_id);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    const char *pathText =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    std::string path = pathText ? pathText : "";
    sqlite3_finalize(stmt);
    return path;
}

bool isLevelAvailable(int id, int level) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT STATUS FROM LEVELS WHERE USER_ID = " + std::to_string(id) +
        " AND LVL_NUM = " + std::to_string(level);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    bool isAvailable = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return isAvailable;
}

void updateLevel(int id, int level, int newLives, int newCoins) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT BEST_LIVES, BEST_COINS FROM LEVELS WHERE USER_ID = " +
        std::to_string(id) + " AND LVL_NUM = " + std::to_string(level);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    int bestLives = std::max(sqlite3_column_int(stmt, 0), newLives);
    int bestCoins = std::max(sqlite3_column_int(stmt, 1), newCoins);
    sql = "UPDATE LEVELS SET BEST_LIVES = " + std::to_string(bestLives) +
          ", BEST_COINS = " + std::to_string(bestCoins) +
          " WHERE USER_ID = " + std::to_string(id) +
          " AND LVL_NUM = " + std::to_string(level);
    char *err = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (rc != SQLITE_OK) {
        std::cerr << "Update records error: " << err << '\n';
        sqlite3_free(err);
    }
    if (level < Game::levelsCount) {
        sql = "UPDATE LEVELS SET STATUS = 1 WHERE USER_ID = " +
              std::to_string(id) +
              " AND LVL_NUM = " + std::to_string(level + 1);
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
        if (rc != SQLITE_OK) {
            std::cerr << "Update next lvl status error: " << err << '\n';
            sqlite3_free(err);
        }
    }
    sqlite3_finalize(stmt);
}

/* void addLevelsForUser(int id, int Game::levelsCount) {
    std::string sql;
    char *err = 0;
    sql = "INSERT INTO LEVELS (USER_ID, LVL_NUM, STATUS) VALUES (" +
          std::to_string(id) + ", 1, 1)";
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    for (int i = 2; i <= Game::levelsCount; ++i) {
        sql = "INSERT INTO LEVELS (USER_ID, LVL_NUM, STATUS) VALUES (" +
              std::to_string(id) + ", " + std::to_string(i) + ", 0)";
        int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
        if (rc != SQLITE_OK) {
            std::cerr << "Add levels error: " << err << '\n';
            sqlite3_free(err);
        }
    }
} */

void updateSkin(int id, int newSkin) {
    if (getCurrentSkinNum(id) == newSkin) {
        return;
    }
    sqlite3_stmt *stmt;
    std::string sql =
        "UPDATE USERS SET CURRENT_SKIN = " + std::to_string(newSkin) +
        " WHERE USER_ID = " + std::to_string(id);
    char *err = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (rc != SQLITE_OK) {
        std::cerr << "Update skin error: " << err << '\n';
        sqlite3_free(err);
    }
    sqlite3_finalize(stmt);
}

bool isSkinAvailable(int id, int skin) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT STATUS FROM SKINS WHERE USER_ID = " + std::to_string(id) +
        " AND ITEM_ID = " + std::to_string(skin);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    bool isAvailable = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return isAvailable;
}

int getSkinCost(int skin) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT COST FROM ITEMS WHERE ITEM_ID = " + std::to_string(skin);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    return sqlite3_column_int(stmt, 0);
}

void buySkin(int id, int skin) {
    int skinCost = getSkinCost(skin);
    std::string sql =
        "UPDATE SKINS SET STATUS = 1 WHERE USER_ID = " + std::to_string(id) +
        " AND ITEM_ID = " + std::to_string(skin);
    char *err = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (rc != SQLITE_OK) {
        std::cerr << "Buy skin error: " << err << '\n';
        sqlite3_free(err);
    }
    updateBalance(id, getBalance(id) - skinCost);
    updateSkin(id, skin);
}

bool buyResume(int id, int resumeCost) {
    if (getBalance(id) < resumeCost) {
        return false;
    }
    updateBalance(id, getBalance(id) - resumeCost);
    return true;
}

LvlRecords getLevelRecords(int id, int level) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT BEST_LIVES, BEST_COINS FROM LEVELS WHERE USER_ID = " +
        std::to_string(id) + " AND LVL_NUM = " + std::to_string(level);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    LvlRecords info;
    info.lives = sqlite3_column_int(stmt, 0);
    info.coins = sqlite3_column_int(stmt, 1);
    sqlite3_finalize(stmt);
    return info;
}

}  // namespace super_hse
