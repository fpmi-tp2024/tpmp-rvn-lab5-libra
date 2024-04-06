#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <sqlite3.h>
#include "validator.h"

class Driver
{
private:
    int id;
    std::string name;
    std::string category;
    std::string startWorkDate;
    std::string password;
    int birthYear;
    std::string login;
    std::string address;

public:
    Driver(int id, const std::string &name, const std::string &category, const std::string &startWorkDate, const std::string password,
           int birthYear, const std::string &login, const std::string &address);
    Driver(sqlite3_stmt *statement);

    int getId() const;
    std::string getName() const;
    std::string getLogin() const;
    std::string getCategory() const;
    std::string getStartWorkDate() const;
    std::string getAddress() const;
    std::string getPassword() const;
    int getBirthYear() const;

    void setName(const std::string &name);
    void setLogin(const std::string &login);
    void setCategory(const std::string &category);
    void setAddress(const std::string &address);
};

#endif // DRIVER_H
