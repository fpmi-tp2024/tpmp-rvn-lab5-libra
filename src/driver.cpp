#include "../include/driver.h"

Driver::Driver(int id, const std::string &name, const std::string &login, const std::string &category,
               long startWorkDate, const std::string &address, int birthYear)
    : id(id), name(name), login(login), category(category), startWorkDate(startWorkDate),
      address(address), birthYear(birthYear) {}

Driver::Driver(sqlite3_stmt *statement)
{
    id = sqlite3_column_int(statement, 0);
    name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1)));
    login = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 2)));
    category = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 3)));
    startWorkDate = sqlite3_column_int64(statement, 4);
    address = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 5)));
    birthYear = sqlite3_column_int(statement, 6);
}

int Driver::getId() const
{
    return id;
}

std::string Driver::getName() const
{
    return name;
}

std::string Driver::getLogin() const
{
    return login;
}

std::string Driver::getCategory() const
{
    return category;
}

long Driver::getStartWorkDate() const
{
    return startWorkDate;
}

std::string Driver::getAddress() const
{
    return address;
}

int Driver::getBirthYear() const
{
    return birthYear;
}
