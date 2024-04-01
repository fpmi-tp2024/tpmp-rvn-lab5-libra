#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include<string>
#include<sqlite3.h>

//Класс для вспомогательных функций для работы с базой данных
class DatabaseHelper {
public:
    static bool isTableEmpty(sqlite3* db, const std::string& tableName);
};

#endif // DATABASEHELPER_H