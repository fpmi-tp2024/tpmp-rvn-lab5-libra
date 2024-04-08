#include "../include/driverstorer.h"

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
        "login text NOT NULL UNIQUE,"
        "password_hash text NOT NULL,"
        "name varchar(30) NOT NULL,"
        "category varchar(5) NOT NULL,"
        "start_work_date text NOT NULL DEFAULT (strftime('%d-%m-%Y', 'now')),"
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
}

// #TODO : возможно стоит переделать, чтобы возращался вектор
std::pair<Driver, int> DriverStorer::getDriverWithMinimumTripsAndMoney()
{
    char *err_msg = nullptr;
    std::string SQLQuery =
        "SELECT Dr.id,Dr.login,Dr.name,Dr.category,Dr.start_work_date, "
        "Dr.birth_year,Dr.address "
        "FROM "
        "Drivers AS Dr "
        "LEFT JOIN "
        "Orders AS Ord "
        "ON Dr.login = Ord.driver_login "
        "GROUP BY Dr.login "
        "ORDER BY Count(Ord.date) ASC "
        "LIMIT 1; ";

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    result = sqlite3_step(stmt);
    if (result != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get driver with minimum trips");
    }

    Driver driver(stmt);
    sqlite3_finalize(stmt);

    SQLQuery = "SELECT SUM(transport_cost) FROM Orders WHERE driver_login = '" + driver.getLogin() + "';";

    result = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    result = sqlite3_step(stmt);
    if (result != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get driver with minimum trips");
    }

    int sum = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return std::make_pair(driver, sum);
}

void DriverStorer::updateAddress(int driverId, const std::string &address)
{
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

void DriverStorer::updateLogin(int driverId, const std::string &login)
{
    char *err_msg = nullptr;
    std::string SQLQuery = "UPDATE Drivers SET login = '" + login + "' WHERE id = " + std::to_string(driverId) + ";";

    int result = sqlite3_exec(this->db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't update login: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }
}

void DriverStorer::updatePassword(int driverId, const std::string &password)
{
    // #TODO : возможно стоит добавить хеширование пароля
    char *err_msg = nullptr;
    std::string SQLQuery = "UPDATE Drivers SET password_hash = '" + password + "' WHERE id = " + std::to_string(driverId) + ";";

    int result = sqlite3_exec(this->db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't update password: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }
}

void DriverStorer::addDriver(const Driver &driver,std::string passwordHash)
{
    char *err_msg = nullptr;
    std::string SQLQuery =
        "INSERT INTO Drivers(login,name,category,start_work_date,birth_year,address,password_hash) "
        "VALUES('" +
        driver.getLogin() + "','" + driver.getName() + "','" + driver.getCategory() + "'," + std::to_string(driver.getStartWorkDate()) + "," + std::to_string(driver.getBirthYear()) + ",'" + driver.getAddress() + "','" + passwordHash + "');";

    int result = sqlite3_exec(this->db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't add driver: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }
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

std::vector<Order> DriverStorer::getOrdersByDriverAndPeriod(int driverId, long startDate, long endDate){
    std::vector<Order> result;
    char *err_msg = nullptr;

    std::string SQLQuery = "SELECT * FROM Orders WHERE driver_id = " + std::to_string(driverId) + " AND date BETWEEN " + std::to_string(startDate) + " AND " + std::to_string(endDate) + ";";

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

std::vector<Driver> DriverStorer::getDrivers(){
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

Driver DriverStorer::getDriverById(const int driverID){
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

Driver DriverStorer::getDriverByLogin(const std::string& login){
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

Driver DriverStorer::getDriverByLoginAndPassword(const std::string &login, const std::string &password){
    char *err_msg = nullptr;
    std::string SQLQuery = "SELECT * FROM Drivers WHERE login = '" + login + "' AND password_hash = '" + password + "';";

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
        throw std::runtime_error("Can't get driver by login and password");
    }

    Driver driver(stmt);
    sqlite3_finalize(stmt);

    return driver;
}