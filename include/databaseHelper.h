#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <string>
#include <ctime>
#include <sqlite3.h>

// Класс для вспомогательных функций для работы с базой данных
class DatabaseHelper
{
public:
    static bool isTableEmpty(sqlite3 *db, const std::string &tableName);
    static long dateToSec(int year, int month, int day);
    static std::string secToDate(long sec);
};

#endif // DATABASEHELPER_H