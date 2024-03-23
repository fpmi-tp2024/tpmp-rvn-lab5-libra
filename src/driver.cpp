#include "../include/driver.h"

Driver::Driver(int id, const std::string &name, const std::string &login, const std::string &category,
               long startWorkDate, const std::string &address, int birthYear)
    : id(id), name(name), login(login), category(category), startWorkDate(startWorkDate),
      address(address), birthYear(birthYear) {}

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
