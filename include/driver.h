#ifndef DRIVER_H
#define DRIVER_H

#include <string>

class Driver {
private:
    int id;
    std::string name;
    std::string login;
    std::string category;
    long startWorkDate;
    std::string address;
    int birthYear;

public:
    Driver(int id, const std::string& name, const std::string& login, const std::string& category,
           long startWorkDate, const std::string& address, int birthYear);

    int getId() const;
    std::string getName() const;
    std::string getLogin() const;
    std::string getCategory() const;
    long getStartWorkDate() const;
    std::string getAddress() const;
    int getBirthYear() const;
};

#endif // DRIVER_H
