#include "../include/driver.h"
#include <iostream>

Driver::Driver(int id, const std::string &login, const std::string &name, const std::string &category, const long &startWorkDate,
               int birthYear, const std::string &address) : id(id), startWorkDate(startWorkDate), birthYear(birthYear)
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
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 3))),
          std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 4))),
          sqlite3_column_int(statement, 5),
          sqlite3_column_int(statement, 6),
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

void Driver::setId(int id)
{
    if (this->id != -1)
    {
        throw std::invalid_argument("Id is already set.");
    }
    this->id = id;
}

std::string Driver::toString() const
{
    std::stringstream ss;
    ss << "||\tID: " << id << "\n";
    ss << "||\tName: " << name << "\n";
    ss << "||\tLogin: " << login << "\n";
    ss << "||\tCategory: " << category << "\n";
    ss << "||\tStart work date: " << startWorkDate << "\n";
    ss << "||\tBirth year: " << birthYear << "\n";
    ss << "||\tAddress: " << address << "\n";
    return ss.str();
}