#include "../include/carstorer.h"

CarStorer::CarStorer(const std::string& dbName)
{
    char* err_msg = nullptr;

    // Открываем базу данных 
    int result = sqlite3_open(dbName.c_str(), &this->db);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        throw std::runtime_error("Can't open database,try to restart application " + std::string(sqlite3_errmsg(db)));
    }

    const char* SQLQuery =
        "CREATE TABLE IF NOT EXISTS Cars ("
        "number varchar(10) NOT NULL PRIMARY KEY,"
        "brand varchar(15) NOT NULL,"
        "model varchar(15) NOT NULL,"
        "capacity integer NOT NULL,"
        "purchase_mileage integer NOT NULL"
        ");";

    // Создаем таблицу Cars
    result = sqlite3_exec(this->db, SQLQuery, 0, 0, &err_msg);
    if (result != SQLITE_OK) {
        std::string error_message = "Can't create table Cars: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    SQLQuery =
        "INSERT INTO Cars(number,brand,model,capacity,purchase_mileage)"
        "VALUES"
        "('A123BC','Volvo','XC90',2500,10000),"
        "('B456CD','BMW','X5',3000,20000),"
        "('C789EF','Audi','Q7',35000,30000),"
        "('D012GH','Mercedes','GLE',4000,40000),"
        "('E345IJ','Toyota','Land Cruiser',4500,50000);";

    // Заполняем таблицу Cars первоначальными данными
    if(DatabaseHelper::isTableEmpty(this->db, "Cars")) {
        result = sqlite3_exec(this->db, SQLQuery, 0, 0, &err_msg);
        if (result != SQLITE_OK) {
            std::string error_message = "Can't insert data into Cars: " + std::string(err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            throw std::runtime_error(error_message);
        }
    }


}