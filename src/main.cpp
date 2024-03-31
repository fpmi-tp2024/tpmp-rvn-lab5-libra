#include "../include/menuinterface.h"
#include "../include/driverstorer.h"
#include "../config/config.hpp"

int main()
{
    std::cout << Config::getString("admine_password") << std::endl;
    std::cout << Config::getInt("commission_fees") << std::endl;
    std::cout << Config::getInt("MAX_COST") << std::endl;

    startMenu();

    return 0;
}