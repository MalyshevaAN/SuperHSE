#include "sql.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "../sqlite/sqlite3.h"

namespace super_hse {
sqlite3 *db;
int levelsCount = 4;

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

[[nodiscard]] std::string getUsername(int id) {
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

[[nodiscard]] int getBalance(int id) {
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
    std::string sql = "INSERT INTO USERS (USERNAME, PASSWORD) VALUES ('" +
                      username + "', '" + password + "')";
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
    for (int i = 1; i <= levelsCount; ++i) {
        sql = "INSERT INTO LEVELS (USER_ID, LVL_NUM, STATUS) VALUES (" +
              std::to_string(id) + ", " + std::to_string(i) + ", " +
              (i == 1 ? "1" : "0") + ")";
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
        if (rc != SQLITE_OK) {
            std::cerr << "Add levels error: " << err << '\n';
            sqlite3_free(err);
        }
    }

    return true;
}

[[nodiscard]] int
loginUser(const std::string &username, const std::string &password) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT USER_ID FROM USERS WHERE USERNAME = ? AND PASSWORD = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    int step = sqlite3_step(stmt);
    int id = -1;
    if (step == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return id;
}

[[nodiscard]] std::string getCurrentSkin(int id) {
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

[[nodiscard]] bool isLevelAvailable(int id, int level) {
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

void updateLevel(int id, int level, int newLives, int newCash) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT BEST_LIVES, BEST_CASH FROM LEVELS WHERE USER_ID = " +
        std::to_string(id) + " AND LVL_NUM = " + std::to_string(level);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    int bestLives = std::max(sqlite3_column_int(stmt, 0), newLives);
    int bestCash = std::max(sqlite3_column_int(stmt, 1), newCash);
    sql = "UPDATE LEVELS SET BEST_LIVES = " + std::to_string(bestLives) +
          ", BEST_CASH = " + std::to_string(bestCash) +
          " WHERE USER_ID = " + std::to_string(id) +
          " AND LVL_NUM = " + std::to_string(level);
    char *err = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (rc != SQLITE_OK) {
        std::cerr << "Update records error: " << err << '\n';
        sqlite3_free(err);
    }
    if (level < levelsCount) {
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

void addLevelsForUser(int id, int levelsCount) {
    std::string sql;
    char *err = 0;
    sql = "INSERT INTO LEVELS (USER_ID, LVL_NUM, STATUS) VALUES (" +
          std::to_string(id) + ", 1, 1)";
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    for (int i = 2; i <= levelsCount; ++i) {
        sql = "INSERT INTO LEVELS (USER_ID, LVL_NUM, STATUS) VALUES (" +
              std::to_string(id) + ", " + std::to_string(i) + ", 0)";
        int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
        if (rc != SQLITE_OK) {
            std::cerr << "Add levels error: " << err << '\n';
            sqlite3_free(err);
        }
    }
}

void updateSkin(int id, int newSkin) {
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

LvlRecords getLevelRecords(int id, int level) {
    sqlite3_stmt *stmt;
    std::string sql =
        "SELECT BEST_LIVES, BEST_CASH FROM LEVELS WHERE USER_ID = " +
        std::to_string(id) + " AND LVL_NUM = " + std::to_string(level);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    LvlRecords info;
    info.lives = sqlite3_column_int(stmt, 0);
    info.cash = sqlite3_column_int(stmt, 1);
    sqlite3_finalize(stmt);
    return info;
}

}  // namespace super_hse
