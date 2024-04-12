#include "../include/driverstorer.h"
#include <iostream>

DriverStorer::DriverStorer(const std::string &dbName)
{
    char *err_msg = nullptr;

    // Открываем базу данных
    int result = sqlite3_open(dbName.c_str(), &this->db);
    if (result != SQLITE_OK)
    {
        sqlite3_close(db);
        throw std::runtime_error("Can't open database,try to restart application " + std::string(sqlite3_errmsg(db)));
    }

    std::string SQLQuery =
        "CREATE TABLE IF NOT EXISTS Drivers ("
        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
        "login text NOT NULL REFERENCES Users(login) ON UPDATE CASCADE ON DELETE CASCADE,"
        "name varchar(30) NOT NULL,"
        "category varchar(5) NOT NULL,"
        "start_work_date INTEGER NOT NULL DEFAULT (strftime('%s', 'now')),"
        "birth_year integer NOT NULL,"
        "address text NOT NULL"
        ");";

    // Создаем таблицу Drivers
    result = sqlite3_exec(this->db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't create table Drivers: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
}

std::pair<Driver, double> DriverStorer::getDriverWithMinimumTripsAndMoney()
{
    char *err_msg = nullptr;
    std::string SQLQuery = "SELECT * FROM Drivers WHERE id = (SELECT driver_id FROM Orders GROUP BY driver_id ORDER BY COUNT(driver_id) ASC LIMIT 1);";

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get driver with minimum trips");
    }

    Driver driver(stmt);
    sqlite3_finalize(stmt);

    SQLQuery = "SELECT SUM(cost) FROM Orders WHERE driver_id = " + std::to_string(driver.getId()) + ";";

    res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get money of driver with minimum trips");
    }

    double money = sqlite3_column_double(stmt, 0) * Config::getInt("commission_fees") / 100.0;
    sqlite3_finalize(stmt);

    return std::make_pair(driver, money);
}

void DriverStorer::updateAddress(int driverId, const std::string &address)
{
    if (!Validator::isValidAddress(address))
    {
        throw std::runtime_error("Invalid address");
    }

    char *err_msg = nullptr;
    std::string SQLQuery = "UPDATE Drivers SET address = '" + address + "' WHERE id = " + std::to_string(driverId) + ";";

    int result = sqlite3_exec(this->db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't update address: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }
}

void DriverStorer::addDriver(Driver &driver)
{
    char *err_msg = nullptr;
    std::string SQLQuery =
        "INSERT INTO Drivers(login,name,category,start_work_date,birth_year,address) "
        "VALUES('" +
        driver.getLogin() + "','" + driver.getName() + "','" + driver.getCategory() + "'," + std::to_string(driver.getStartWorkDate()) + "," + std::to_string(driver.getBirthYear()) + ",'" + driver.getAddress() + "');";

    int result = sqlite3_exec(this->db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't add driver: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    driver.setId(sqlite3_last_insert_rowid(db));
}

void DriverStorer::removeDriver(int driverId)
{
    char *err_msg = nullptr;
    std::string SQLQuery = "DELETE FROM Drivers WHERE id = " + std::to_string(driverId) + ";";

    int result = sqlite3_exec(this->db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't remove driver: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }
}

DriverStorer::~DriverStorer()
{
    sqlite3_close(db);
}

std::vector<Order> DriverStorer::getOrdersByDriverAndPeriod(int driverId, long startDate, long endDate)
{
    std::vector<Order> result;
    char *err_msg = nullptr;

    std::string SQLQuery;
    
    if (endDate==-1 && startDate==-1){
        SQLQuery = "SELECT * FROM Orders WHERE driver_id = " + std::to_string(driverId) + ";";
    }else{
        SQLQuery = "SELECT * FROM Orders WHERE driver_id = " + std::to_string(driverId) + " AND date BETWEEN " + std::to_string(startDate) + " AND " + std::to_string(endDate) + ";";
    }

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result.push_back(Order(stmt));
    }

    return result;
}

std::vector<Driver> DriverStorer::getDrivers()
{
    std::vector<Driver> result;
    char *err_msg = nullptr;

    std::string SQLQuery = "SELECT * FROM Drivers;";

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result.push_back(Driver(stmt));
    }

    return result;
}

Driver DriverStorer::getDriverById(const int driverID)
{
    char *err_msg = nullptr;
    std::string SQLQuery = "SELECT * FROM Drivers WHERE id = " + std::to_string(driverID) + ";";

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get driver by id");
    }

    Driver driver(stmt);
    sqlite3_finalize(stmt);

    return driver;
}

Driver DriverStorer::getDriverByLogin(const std::string &login)
{
    char *err_msg = nullptr;
    std::string SQLQuery = "SELECT * FROM Drivers WHERE login = '" + login + "';";

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get driver by login");
    }

    Driver driver(stmt);
    sqlite3_finalize(stmt);

    return driver;
}