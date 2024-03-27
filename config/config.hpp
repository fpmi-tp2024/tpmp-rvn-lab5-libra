#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>

class Config
{
private:
    std::map<std::string, std::string> config;

    Config()
    {
        std::ifstream file("config/config.txt");
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open config file: config.txt");
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value))
            {
                value.pop_back();
                config[key] = value;
            }
        }

        file.close();
    }

public:
    static Config &getInstance()
    {
        static Config instance;
        return instance;
    }

    static std::string getString(const std::string &key)
    {
        auto &instance = getInstance();

        auto it = instance.config.find(key);
        if (it != instance.config.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("Key not found in config file: " + key);
        }
    }

    static int getInt(const std::string &key)
    {
        auto &instance = getInstance();

        auto it = instance.config.find(key);
        if (it != instance.config.end())
        {
            try
            {
                return std::stoi(it->second);
            }
            catch (const std::invalid_argument &e)
            {
                throw std::runtime_error("Invalid value for key in config file: " + key);
            }
        }
        else
        {
            throw std::runtime_error("Key not found in config file: " + key);
        }
    }
};

#endif // CONFIG_H
