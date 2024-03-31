#include "../include/menu.h"
#include "../include/driverstorer.h"
#include "../config/config.hpp"

int main()
{
    std::cout << sum(1, 2) << std::endl;

    std::cout << Config::getString("admine_password") << std::endl;
    std::cout << Config::getInt("commission_fees") << std::endl;
    std::cout << Config::getInt("MAX_COST") << std::endl;

    startMenu();

    return 0;
}