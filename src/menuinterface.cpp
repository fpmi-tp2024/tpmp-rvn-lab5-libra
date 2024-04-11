#include <string>
#include <iostream>
#include "../include/admininterface.h"
#include "../include/driverinterface.h"
#include "../include/utilfuntions.h"
#include "../include/menuinterface.h"

MenuInterface::MenuInterface() {}

void MenuInterface::run()
{
	int option;
	std::string input;

	std::cout << "||\tSelect account type:\n";
	std::cout << "||\t1: Admin\n";
	std::cout << "||\t2: Driver\n";
	std::cout << "||\n";
	std::cout << "||\tOr type \"q\" to quit\n";
	std::cin >> input;
	trim(input);

	while (!tryParseString(input, option) || (option != 1 && option != 2))
	{
		if (tryQuit(input))
		{
			return;
		}

		std::cout << "||\tYour input is not valid. Try again\n";
		std::cin >> input;
		trim(input);
	}

	if (option == 1)
	{
		AdminInterface adminInterface;

		adminInterface.run();
	}
	else
	{
		DriverInterface driverInterface;

		driverInterface.run();
	}
}

MenuInterface::~MenuInterface() {}