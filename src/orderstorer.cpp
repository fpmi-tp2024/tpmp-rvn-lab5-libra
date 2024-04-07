#include "../include/orderstorer.h"

OrderStorer::OrderStorer(const std::string &dbName)
{
    char *err_msg = nullptr;

    // Открываем базу данных
    int result = sqlite3_open(dbName.c_str(), &this->db);
    if (result != SQLITE_OK)
    {
        sqlite3_close(db);
        throw std::runtime_error("Can't open database,try to restart application " + std::string(sqlite3_errmsg(db)));
    }

    const char *SQLQuery =
        "CREATE TABLE IF NOT EXISTS Orders ("
        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
        "date text NOT NULL DEFAULT (strftime('%d-%m-%Y', 'now')),"
        "kilometrage integer NOT NULL,"
        "cargo_weight integer NOT NULL,"
        "transport_cost integer NOT NULL,"
        "driver_login text NOT NULL UNIQUE REFERENCES Drivers(login),"
        "car_number varchar(10) NOT NULL UNIQUE REFERENCES Cars(number)"
        ");";

    // Создаем таблицу Orders
    result = sqlite3_exec(this->db, SQLQuery, 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't create table Orders: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }
}