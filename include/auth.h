#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <openssl/sha.h>
#include <sqlite3.h>
#include <iostream>
#include <stdexcept>

enum class UserType
{
    ADMIN,
    DRIVER
};

class Auth
{
private:
    sqlite3 *db;

public:
    Auth(const std::string &db_name);
    ~Auth();

    bool userExists(const std::string &login);
    UserType checkPassword(const std::string &login, const std::string &password);
    void addUser(const std::string &login, const std::string &password, UserType user_type);
    void deleteUser(const std::string &login);
};

#endif // AUTH_H
