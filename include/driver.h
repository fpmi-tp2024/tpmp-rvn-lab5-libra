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
    int birthYear;
    std::string address;

public:
    Driver() {}
    Driver(int id, const std::string &login, const std::string &name, const std::string &category, const long &startWorkDate,
           int birthYear, const std::string &address);
    Driver(sqlite3_stmt *statement);

    int getId() const;
    std::string getName() const;
    std::string getLogin() const;
    std::string getCategory() const;
    long getStartWorkDate() const;
    std::string getAddress() const;
    int getBirthYear() const;

    void setId(int id);
    void setName(const std::string &name);
    void setLogin(const std::string &login);
    void setCategory(const std::string &category);
    void setAddress(const std::string &address);

    std::string toString() const;
};

#endif // DRIVER_H
