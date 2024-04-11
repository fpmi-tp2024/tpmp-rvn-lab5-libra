#include "../include/auth.h"

Auth::Auth(const std::string &db_name)
{
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot open database: " + std::string(sqlite3_errmsg(db)));
    }

    std::string query = "CREATE TABLE IF NOT EXISTS Users ("
                        "login TEXT PRIMARY KEY,"
                        "password TEXT NOT NULL,"
                        "user_type TEXT NOT NULL"
                        ");";

    char *err_msg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot create table users: " + std::string(err_msg));
    }
}

Auth::~Auth()
{
    sqlite3_close(db);
}

bool Auth::userExists(const std::string &login)
{
    std::string query = "SELECT COUNT(*) FROM Users WHERE login='" + login + "';";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot prepare statement: " + std::string(sqlite3_errmsg(db)));
    }

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        throw std::runtime_error("Cannot check if user exists.");
    }

    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return count > 0;
}

UserType Auth::checkPassword(const std::string &login, const std::string &password)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password.c_str(), password.length());
    SHA256_Final(hash, &ctx);

    std::string query = "SELECT user_type FROM Users WHERE login='" + login + "' AND password='";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        query += std::to_string((int)hash[i]) + ".";
    }
    query += "';";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot prepare statement: " + std::string(sqlite3_errmsg(db)));
    }

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        throw std::runtime_error("Invalid login or password");
    }

    int user_type = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return static_cast<UserType>(user_type);
}

void Auth::addUser(const std::string &login, const std::string &password, UserType user_type)
{
    if (userExists(login))
    {
        throw std::runtime_error("User with login '" + login + "' already exists.");
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password.c_str(), password.length());
    SHA256_Final(hash, &ctx);

    std::string query = "INSERT INTO Users (login, password, user_type) VALUES ('" + login + "', '";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        query += std::to_string((int)hash[i]) + ".";
    }
    query += "', '" + std::to_string((int)user_type) + "');";

    char *err_msg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot add user: " + std::string(err_msg));
    }
}

void Auth::deleteUser(const std::string &login)
{
    if (!userExists(login))
    {
        throw std::runtime_error("User with login '" + login + "' does not exist.");
    }

    std::string query = "DELETE FROM Users WHERE login='" + login + "';";
    char *err_msg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK)
    {
        throw std::runtime_error("Cannot delete user: " + std::string(err_msg));
    }
}
