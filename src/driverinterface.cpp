#include "../include/driverinterface.h"

DriverInterface::DriverInterface()
{
	driverId = -1;

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
	std::string login;
	std::string password;
	std::string quitStr;

	std::cout << "||\tYou selected Driver account\n";
	std::cout << "||\tEnter Username and Password to proceed\n";
	std::cout << "||\tUsername: ";
	std::cin >> login;
	std::cout << "||\tPassword: ";
	std::cin >> password;
	trim(login);
	trim(password);

	bool isLogged;

	try 
	{
		isLogged = tryLogInDriver(login, password);
	}
	catch (const std::exception &e)
	{
		std::cout << "\033[31m" << "Exception: " << e.what() << "\033[0m" << std::endl;
	}

	while (!isLogged)
	{
		std::cout << "\033[31m||\tUsername or password are not valid. Try again\n"
				  << "||\tIf you want to quit, type \"q\". Otherwise - anything else\n\033[0m";
		std::cin >> quitStr;
		trim(quitStr);
		if (tryQuit(quitStr))
		{
			return;
		}
		std::cout << "||\tUsername: ";
		std::cin >> login;
		std::cout << "||\tPassword: ";
		std::cin >> password;
		trim(login);
		trim(password);
		try 
		{
			isLogged = tryLogInDriver(login, password);
		}
		catch (const std::exception &e)
		{
			std::cout << "\033[31m" << "Exception: " << e.what() << "\033[0m" << std::endl;
		}
	}

	std::cout << "\033[32m||\tSuccessfully logged in\n\033[0m";

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

bool DriverInterface::tryLogInDriver(const std::string &login, const std::string &password)
{
	driverId = driverStorer.getDriverByLoginAndPassword(login, password).getId();
	return true;
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

	std::vector<Order> orders(driverStorer.getOrdersByDriverAndPeriod(driverId, startDate, endDate));

	std::cout << "\033[32m";
	for (Order order : orders)
	{
		std::cout << order.toString();
	}
	std::cout << "\033[0m";
}

void DriverInterface::getTotalOrdersCount()
{
	std::cout << "\033[32m||\t" << orderStorer.getTotalNumberOfOrders(driverId) << "\n\033[0m";
}

void DriverInterface::getTotalWeightOfTransportedGoods()
{
	std::cout << "\033[32m||\t" << orderStorer.getTotalCargoMass(driverId) << "\n\033[0m";
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

	std::cout << "\033[32m||\t" << orderStorer.getTotalMoney(driverId, startDate, endDate) << "\n\033[0m";
}

void DriverInterface::getMoneyEarned()
{
	std::cout << "\033[32m||\t" << orderStorer.getTotalMoney(driverId) << "\n\033[0m";
}

void DriverInterface::changeAddress()
{
	std::string newAddress;

	std::cout << "||\tEnter new address\n";
	std::cin >> newAddress;

	driverStorer.updatePassword(driverId, newAddress);
}

void DriverInterface::changeLogin()
{
	std::string newLogin;

	std::cout << "||\tEnter new login\n";
	std::cin >> newLogin;

	driverStorer.updatePassword(driverId, newLogin);
}

void DriverInterface::changePassword()
{
	std::string newPassword;

	std::cout << "||\tEnter new password\n";
	std::cin >> newPassword;

	driverStorer.updatePassword(driverId, newPassword);
}