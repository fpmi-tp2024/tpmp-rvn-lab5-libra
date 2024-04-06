#include "../include/driver.h"
#include <iostream>

Driver::Driver(int id, const std::string &name, const std::string &category, const std::string &startWorkDate, const std::string password,
               int birthYear, const std::string &login, const std::string &address) : id(id), startWorkDate(startWorkDate), birthYear(birthYear), password(password)
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
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 4))),
          sqlite3_column_int(statement, 5),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 6))),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 7)))) {}

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

std::string Driver::getStartWorkDate() const
{
    return startWorkDate;
}

std::string Driver::getPassword() const
{
    return password;
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
    std::cout << address << std::endl;
    if (Validator::isValidAddress(address))
    {
        this->address = address;
    }
    else
    {
        throw std::invalid_argument("Invalid address format.");
    }
}