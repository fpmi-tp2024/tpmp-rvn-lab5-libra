#include "../include/databaseHelper.h"
#include <iostream>

bool DatabaseHelper::isTableEmpty(sqlite3 *db, const std::string &tableName)
{
    std::string SQLQuery = "SELECT count(*) FROM " + tableName + ";";
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, SQLQuery.c_str(), -1, &stmt, 0) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            count = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);

    return count == 0;
}

long DatabaseHelper::dateToSec(int year, int month, int day)
{
    if (year < 1900 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        throw std::invalid_argument("Invalid date.Check input information");
    }

    std::tm t = {};
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;
    t.tm_mday = day;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;
    if (std::mktime(&t) == -1)
    {
        std::cerr << "Error: unable to make time using mktime\n";
        return -1;
    }

    return std::mktime(&t);
}

std::string DatabaseHelper::secToDate(long sec)
{
    std::tm *t = std::localtime(&sec);
    if (t == nullptr)
    {
        std::cerr << "Error: unable to make time using localtime\n";
        return "";
    }

    return std::to_string(t->tm_mday) + "." + std::to_string(t->tm_mon + 1) + "." + std::to_string(t->tm_year + 1900);
}