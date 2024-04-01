#include "../include/driver.h"

Driver::Driver(int id, const std::string &name, const std::string &login, const std::string &category,
               long startWorkDate, const std::string &address, int birthYear) : id(id), startWorkDate(startWorkDate), birthYear(birthYear)
{
    setName(name);
    setLogin(login);
    setCategory(category);
    setAddress(address);
}

Driver::Driver(sqlite3_stmt *statement)
    : Driver(
          sqlite3_column_int(statement, 0),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1))),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 2))),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 3))),
          sqlite3_column_int64(statement, 4),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 5))),
          sqlite3_column_int(statement, 6)) {}

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

void Driver::setName(const std::string &name)
{
    if (Validator::isValidName(name))
    {
        this->name = name;
    }
    else
    {
        throw std::invalid_argument("Invalid name format.");
    }
}

void Driver::setLogin(const std::string &login)
{
    if (Validator::isValidLogin(login))
    {
        this->login = login;
    }
    else
    {
        throw std::invalid_argument("Invalid login format.");
    }
}

void Driver::setCategory(const std::string &category)
{
    if (Validator::isValidCategory(category))
    {
        this->category = category;
    }
    else
    {
        throw std::invalid_argument("Invalid category format.");
    }
}

void Driver::setAddress(const std::string &address)
{
    if (Validator::isValidAddress(address))
    {
        this->address = address;
    }
    else
    {
        throw std::invalid_argument("Invalid address format.");
    }
}