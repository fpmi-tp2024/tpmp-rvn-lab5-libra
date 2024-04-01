#include "../include/driverstorer.h"

DriverStorer::DriverStorer(const std::string& dbName)
{
    char* err_msg = nullptr;

    // Открываем базу данных 
    int result = sqlite3_open(dbName.c_str(), &this->db);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        throw std::runtime_error("Can't open database,try to restart application " + std::string(sqlite3_errmsg(db)));
    }

    const char* SQLQuery =
        "CREATE TABLE IF NOT EXISTS Drivers ("
        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
        "name varchar(30) NOT NULL,"
        "category varchar(5) NOT NULL,"
        "experience integer NOT NULL,"
        "password_hash text NOT NULL UNIQUE,"
        "birth_year integer NOT NULL,"
        "login text NOT NULL,"
        "address text NOT NULL"
    ");";

    // Создаем таблицу Drivers
    result = sqlite3_exec(this->db, SQLQuery, 0, 0, &err_msg);
    if (result != SQLITE_OK) {
        std::string error_message = "Can't create table Drivers: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    SQLQuery =
        "INSERT INTO Drivers(name,category,experience,password_hash,birth_year,login,address)"
        "VALUES"
        "('Иванов Алексей','A','5','123456',1990,'ivanov','г.Минск ул.Смирнова д.17'),"
        "('Петров Василий','B','3','12345632',1995,'petrov','г. Слуцк ул.Зеленая д.5а'),"
        "('Сидоров Иван','C','1','1234562332',2000,'sidorov','г.Слуцк ул.Молодежная д.121'),"
        "('Кузнецов Петр','D','2','1',1998,'kuznecov','г.Минск ул.Октябрьская д.10'),"
        "('Смирнов Александр','A','4','12345689898',1992,'smirnov','г.Минск ул.Карла Маркса д.127');";

    // Заполняем таблицу Drivers первоначальными данными
    if(DatabaseHelper::isTableEmpty(this->db, "Drivers")) {
        result = sqlite3_exec(this->db, SQLQuery, 0, 0, &err_msg);
        if (result != SQLITE_OK) {
            std::string error_message = "Can't insert data into Drivers: " + std::string(err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            throw std::runtime_error(error_message);
        }
    }

}