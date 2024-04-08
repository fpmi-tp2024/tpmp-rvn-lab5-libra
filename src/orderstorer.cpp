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
        "date integer NOT NULL DEFAULT (strftime('%s', 'now')),"
        "kilometrage integer NOT NULL,"
        "cargo_weight integer NOT NULL,"
        "transport_cost integer NOT NULL,"
        "driver_id integer NOT NULL UNIQUE REFERENCES Drivers(id),"
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

void OrderStorer::addOrder(const Order &order)
{
    char *err_msg = nullptr;
    std::string SQLQuery = "INSERT INTO Orders (date, kilometrage, cargo_weight, transport_cost, driver_id, car_number) VALUES (" + std::to_string(order.getDate()) + ", " + std::to_string(order.getMileage()) + ", " + std::to_string(order.getCargoMass()) + ", " + std::to_string(order.getCost()) + ", '" + std::to_string(order.getDriverId()) + "', '" + order.getCarNumber() + "');";

    int result = sqlite3_exec(this->db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Can't add order: " + std::string(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }
}

OrderStorer::~OrderStorer()
{
    sqlite3_close(db);
}

int OrderStorer::getTotalNumberOfOrders(const int driverID)
{
    char *err_msg = nullptr;
    std::string SQLQuery = "SELECT COUNT(*) FROM Orders WHERE driver_id = " + std::to_string(driverID) + ";";

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    res = sqlite3_step(stmt);
    if (res != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get total number of orders");
    }

    int result = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return result;
}

int OrderStorer::getTotalCargoMass(const int driverID)
{
    char *err_msg = nullptr;
    std::string SQLQuery = "SELECT SUM(cargo_weight) FROM Orders WHERE driver_id = " + std::to_string(driverID) + ";";

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    res = sqlite3_step(stmt);
    if (res != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get total number of orders");
    }

    int result = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return result;
}

int OrderStorer::getTotalMoney(const int driverID, long start, long end)
{
    char *err_msg = nullptr;
    std::string SQLQuery;

    if (start == -1 && end == -1)
    {
        SQLQuery = "SELECT SUM(transport_cost) FROM Orders WHERE driver_id = " + std::to_string(driverID) + ";";
    }
    else
    {
        SQLQuery = "SELECT SUM(transport_cost) FROM Orders WHERE driver_id = " +
                   std::to_string(driverID) + " AND date >= " + std::to_string(start) + " AND date <= " + std::to_string(end) + ";";
    }

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    res = sqlite3_step(stmt);
    if (res != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get total number of orders");
    }

    int result = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return result;
}

void OrderStorer::removeOrder(int orderId)
{
    std::string SQLQuery = "DELETE FROM Orders WHERE id = " + std::to_string(orderId) + ";";

    char *err_msg = nullptr;

    int result = sqlite3_exec(db, SQLQuery.c_str(), 0, 0, &err_msg);
    if (result != SQLITE_OK)
    {
        std::string error_message = "Cannot delete data from Cars: " + std::string(err_msg);
        sqlite3_free(err_msg);
        throw std::runtime_error(error_message);
    }
}


Order OrderStorer::getOrderById(int orderId)
{
    char *err_msg = nullptr;
    std::string SQLQuery = "SELECT * FROM Orders WHERE id = " + std::to_string(orderId) + ";";

    sqlite3_stmt *stmt;
    int res = sqlite3_prepare_v2(this->db, SQLQuery.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK)
    {
        std::string error_message = "Can't prepare statement: " + std::string(sqlite3_errmsg(db));
        sqlite3_close(db);
        throw std::runtime_error(error_message);
    }

    res = sqlite3_step(stmt);
    if (res != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Can't get order by id");
    }

    Order result = Order(stmt);
    sqlite3_finalize(stmt);

    return result;
}   

std::vector<Order> OrderStorer::getAllOrders(){
    std::vector<Order> result;
    char *err_msg = nullptr;

    std::string SQLQuery = "SELECT * FROM Orders;";

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