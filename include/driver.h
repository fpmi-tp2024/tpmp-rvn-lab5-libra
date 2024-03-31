#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <sqlite3.h>
#include "validator.h"

class Driver
{
private:
    int id;
    std::string login;
    std::string name;
    std::string category;
    long startWorkDate;
    std::string address;
    int birthYear;

public:
    Driver(int id, const std::string &name, const std::string &login, const std::string &category,
           long startWorkDate, const std::string &address, int birthYear);
    Driver(sqlite3_stmt *statement);

    int getId() const;
    std::string getName() const;
    std::string getLogin() const;
    std::string getCategory() const;
    long getStartWorkDate() const;
    std::string getAddress() const;
    int getBirthYear() const;

    void setName(const std::string &name);
    void setLogin(const std::string &login);
    void setCategory(const std::string &category);
    void setAddress(const std::string &address);
};

#endif // DRIVER_H
