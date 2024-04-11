#include "../config/config.hpp"
#include <iostream>
#include <vector>

int main()
{
    std::cout << Config::getString("admine_password") << std::endl;

    return 0;
}
