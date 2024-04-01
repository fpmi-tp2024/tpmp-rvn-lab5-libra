#include "../include/databaseHelper.h"
#include<iostream>

bool DatabaseHelper::isTableEmpty(sqlite3* db, const std::string& tableName) {
    std::string SQLQuery = "SELECT count(*) FROM " + tableName + ";";
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, SQLQuery.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);

    return count == 0;
}