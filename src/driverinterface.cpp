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
		{9, &DriverInterface::printDriverInfo},
	};
}

DriverInterface::~DriverInterface() {}

void DriverInterface::run()
{
	std::cout << "\033[32m"
			  << "||\tYou selected Driver account\n"
			  << "\033[0m";

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
							   "||\t2: <Get count of all completed orders>\n"
							   "||\t3: <Get total weight of transported goods>\n"
							   "||\t4: <Get money earned by time interval>\n"
							   "||\t5: <Get total money earned>\n"
							   "||\t6: <Change address>\n"
							   "||\t7: <Change login>\n"
							   "||\t8: <Change password>\n"
							   "||\t9: <Print my info>\n"
							   "||\n"
							   "||\tOr type \"q\" to quit\n";

	std::string invalidInputError = "\033[31m||\tYour input is not valid. Try again\n\033[0m";

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

			driver = driverStorer.getDriverByLogin(login);

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

	std::vector<Order> orders(driverStorer.getOrdersByDriverAndPeriod(driver.getId(), startDate, endDate));

	std::cout << "\033[32m"
			  << "||\tList of completed orders:\n";
	for (Order order : orders)
	{
		std::cout << order.toString();
		std::cout << "||\n";
	}
	std::cout << "\033[0m";
}

void DriverInterface::getTotalOrdersCount()
{
	std::cout << "\033[32m"
			  << "||\tTotal number of orders: "
			  << orderStorer.getTotalNumberOfOrders(driver.getId()) << "\n"
			  << "\033[0m";
}

void DriverInterface::getTotalWeightOfTransportedGoods()
{
	std::cout << "\033[32m"
			  << "||\tTotal weight of transported goods: "
			  << orderStorer.getTotalCargoMass(driver.getId()) << "\n"
			  << "\033[0m";
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

	std::cout << "\033[32m"
			  << "||\tEarned money: " << orderStorer.getTotalMoney(driver.getId(), startDate, endDate) << "\n"
			  << "\033[0m";
}

void DriverInterface::getMoneyEarned()
{

	std::cout << "\033[32m"
			  << "||\tTotal money earned: " << orderStorer.getTotalMoney(driver.getId()) << "\n"
			  << "\033[0m";
}

void DriverInterface::changeAddress()
{
	std::string newAddress;

	std::cout << "||\tEnter new address\n";
	std::cin >> newAddress;

	trim(newAddress);

	if (Validator::isValidAddress(newAddress))
	{
		driverStorer.updateAddress(driver.getId(), newAddress);
		std::cout << "\033[32m"
				  << "||\tAddress successfully updated\n"
				  << "\033[0m";
	}
	else
	{
		std::cout << "\033[31m"
				  << "||\tAddress is not valid\n"
				  << "\033[0m";
	}
}

void DriverInterface::changeLogin()
{
	std::string newLogin;
	std::string password;

	std::cout << "||\tEnter password\n";
	std::cin >> password;
	std::cout << "||\tEnter new login\n";
	std::cin >> newLogin;

	trim(newLogin);

	if (Validator::isValidLogin(newLogin))
	{
		try
		{
			auth.changeLogin(driver.getLogin(), newLogin, password);

			driver = driverStorer.getDriverByLogin(newLogin);

			std::cout << "\033[32m"
					  << "||\tLogin successfully updated\n"
					  << "\033[0m";
		}
		catch (const std::exception &e)
		{
			std::cout << "\033[31m"
					  << "||\t" << e.what() << '\n'
					  << "\033[0m";
		}
	}
	else
	{
		std::cout << "\033[31m"
				  << "||\tLogin is not valid\n"
				  << "\033[0m";
	}
}

void DriverInterface::changePassword()
{
	std::string oldPassword;
	std::string newPassword;

	std::cout << "||\tEnter old password\n";
	std::cin >> oldPassword;
	std::cout << "||\tEnter new password\n";
	std::cin >> newPassword;

	trim(oldPassword);
	trim(newPassword);

	try
	{
		auth.changePassword(driver.getLogin(), oldPassword, newPassword);
		std::cout << "\033[32m"
				  << "||\tPassword successfully updated\n"
				  << "\033[0m";
	}
	catch (const std::exception &e)
	{
		std::cout << "\033[31m"
				  << "||\t" << e.what() << '\n'
				  << "\033[0m";
	}
}

void DriverInterface::printDriverInfo()
{
	std::cout << "\033[32m" << driver.toString()
			  << "\033[0m";
}