#include "../include/driverinterface.h"

DriverInterface::DriverInterface()
{
	commands = {
		{1, &DriverInterface::getListOfCompletedOrdersByTime},
		{2, &DriverInterface::getTotalOrdersCount},
		{3, &DriverInterface::getTotalWeightOfTransportedGoods},
		{4, &DriverInterface::getMoneyEarnedByTime},
		{5, &DriverInterface::getMoneyEarned},
		{6, &DriverInterface::changeAddress},
		{7, &DriverInterface::changeLogin},
		{8, &DriverInterface::changePassword},
	};
}

DriverInterface::~DriverInterface() {}

void DriverInterface::run()
{
	std::cout << "||\tYou selected Driver account\n";

	while (!authorize())
	{
		std::string quitStr;

		std::cout << "\033[31m"
				  << "||\tIf you want to quit, type \"q\". Otherwise - anything else\n"
				  << "\033[0m";

		std::cin >> quitStr;

		trim(quitStr);
		if (tryQuit(quitStr))
		{
			return;
		}
	}

	std::string input;
	int option;

	std::string commandsList = "||\tSelect operation:\n"
							   "||\t1: <Get list of completed orders by time interval>\n"
							   "||\t2: <Get count of all completed orders >\n"
							   "||\t3: <Get total weight of transported goods>\n"
							   "||\t4: <Get money earned by time interval>\n"
							   "||\t5: <Get total money earned>\n"
							   "||\t6: <Change address>\n"
							   "||\t7: <Change login>\n"
							   "||\t8: <Change password>\n"
							   "||\n"
							   "||\tOr type \"q\" to quit\n";

	std::string invalidInputError = "||\tYour input is not valid. Try again\n";

	while (true)
	{
		std::cout << commandsList;
		std::cin >> input;
		trim(input);

		if (input.empty())
		{
			std::cout << "Blank\n";
		}

		if (tryQuit(input))
		{
			return;
		}

		if (!tryParseString(input, option))
		{
			std::cout << invalidInputError;
		}
		else
		{
			auto it = commands.find(option);

			if (it != commands.end())
			{
				try
				{
					(this->*(it->second))();
				}
				catch (const std::exception &e)
				{
					std::cout << "\033[31m"
							  << "Exception: " << e.what() << "\033[0m" << std::endl;
				}
			}
			else
			{
				std::cout << invalidInputError;
			}
		}
	}
}

bool DriverInterface::authorize()
{
	std::string login;
	std::string password;

	std::cout << "||\tEnter login: ";
	std::cin >> login;
	std::cout << "||\tEnter password: ";
	std::cin >> password;

	trim(login);
	trim(password);

	try
	{
		UserType type = auth.checkPassword(login, password);

		if (type == UserType::DRIVER)
		{
			std::cout << "\033[32m"
					  << "||\tSuccessfully logged in\n"
					  << "\033[0m";

			Driver temp = driverStorer.getDriverByLogin(login);
			driver = &temp;

			return true;
		}
		else
		{
			std::cout << "\033[	31m"
					  << "||\tUsername or password are not valid. Try again\n"
					  << "\033[0m";
			return false;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "\033[	31m" << e.what() << "\033[0m" << std::endl;
		return false;
	}
}

void DriverInterface::getListOfCompletedOrdersByTime()
{
	int startDay, startMonth, startYear;
	int endDay, endMonth, endYear;

	std::cout << "||\tEnter start date: DD MM YYYY\n";
	std::cin >> startDay >> startMonth >> startYear;

	std::cout << "||\tEnter end date: DD MM YYYY\n";
	std::cin >> endDay >> endMonth >> endYear;

	long startDate = DatabaseHelper::dateToSec(startYear, startMonth, startDay);
	long endDate = DatabaseHelper::dateToSec(endYear, endMonth, endDay);

	std::vector<Order> orders(driverStorer.getOrdersByDriverAndPeriod(driver->getId(), startDate, endDate));

	for (Order order : orders)
	{
		std::cout << order.toString();
	}
}

void DriverInterface::getTotalOrdersCount()
{
	std::cout << "||\t" << orderStorer.getTotalNumberOfOrders(driver->getId()) << "\n";
}

void DriverInterface::getTotalWeightOfTransportedGoods()
{
	std::cout << "||\t" << orderStorer.getTotalCargoMass(driver->getId()) << "\n";
}

void DriverInterface::getMoneyEarnedByTime()
{
	int startDay, startMonth, startYear;
	int endDay, endMonth, endYear;

	std::cout << "||\tEnter start date: DD MM YYYY\n";
	std::cin >> startDay >> startMonth >> startYear;

	std::cout << "||\tEnter end date: DD MM YYYY\n";
	std::cin >> endDay >> endMonth >> endYear;

	long startDate = DatabaseHelper::dateToSec(startYear, startMonth, startDay);
	long endDate = DatabaseHelper::dateToSec(endYear, endMonth, endDay);

	std::cout << "||\t" << orderStorer.getTotalMoney(driver->getId(), startDate, endDate) << "\n";
}

void DriverInterface::getMoneyEarned()
{
	std::cout << "||\t" << orderStorer.getTotalMoney(driver->getId()) << "\n";
}

void DriverInterface::changeAddress()
{
	std::string newAddress;

	std::cout << "||\tEnter new address\n";
	std::cin >> newAddress;

	driverStorer.updateAddress(driver->getId(), newAddress);
}

void DriverInterface::changeLogin()
{
	// TODO: LEV
}

void DriverInterface::changePassword()
{
	// TODO: LEV
}