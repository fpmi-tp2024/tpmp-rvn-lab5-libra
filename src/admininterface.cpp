#include "../include/admininterface.h"
#include "../config/config.hpp"
#include<limits>

AdminInterface::AdminInterface()
{
	commands = {
		{1, &AdminInterface::getTotalOrdersByDriver},
		{2, &AdminInterface::getTotalWeightByDriver},
		{3, &AdminInterface::getTotalMoneyByDriver},
		{4, &AdminInterface::getTotalMileageAndWeightByCar},
		{5, &AdminInterface::getOrdersListByDriver},
		{6, &AdminInterface::getAllInfoByDriverWithLeastOrders},
		{7, &AdminInterface::getMoneyByEachDriver},
		{8, &AdminInterface::getAllInfoByCarWithHighestMileage},
		{9, &AdminInterface::addDriver},
		{10, &AdminInterface::addCar},
		{11, &AdminInterface::addOrder},
		{12, &AdminInterface::getListOfDrivers},
		{13, &AdminInterface::getListOfCars},
		{14, &AdminInterface::getListOfOrders},
	};
}

AdminInterface::~AdminInterface() {}

void AdminInterface::run()
{
	std::cout << "\033[32m"
			  << "||\tYou selected Admin account\n"
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
							   "||\t1: <Get count of completed orders by driver>\n"
							   "||\t2: <Get total weight delivered by driver>\n"
							   "||\t3: <Get total money aquired by driver>\n"
							   "||\t4: <Get total mileage and orders weight by car>\n"
							   "||\t5: <Get orders list by driver>\n"
							   "||\t6: <Get all info by driver with least completed orders>\n"
							   "||\t7: <Get money by each driver>\n"
							   "||\t8: <Get all info about car with highest mileage>\n"
							   "||\t9: <Add driver>\n"
							   "||\t10: <Add car>\n"
							   "||\t11: <Add order>\n"
							   "||\t12: <Get list of drivers>\n"
							   "||\t13: <Get list of cars>\n"
							   "||\t14: <Get list of orders>\n"
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

bool AdminInterface::authorize()
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

		if (type == UserType::ADMIN)
		{
			std::cout << "\033[32m"
					  << "||\tSuccessfully logged in\n"
					  << "\033[0m";
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

void AdminInterface::getTotalOrdersByDriver()
{
	int driverId;

	driverId=getNumberInput("||\tEnter driver id: \n");

	Driver driver = driverStorer.getDriverById(driverId);

	std::cout << "\033[32m||\tTotal number of completed orders: " << orderStorer.getTotalNumberOfOrders(driverId) << "\033[0m\n";
}

void AdminInterface::getTotalWeightByDriver()
{
	int driverId;

	driverId=getNumberInput("||\tEnter driver id: \n");

	Driver driver = driverStorer.getDriverById(driverId);

	std::cout << "\033[32m||\tTotal weight delivered by driver " << driver.getLogin() << ": " << orderStorer.getTotalCargoMass(driverId) << "\033[0m\n";
}

void AdminInterface::getTotalMoneyByDriver()
{
	int driverId;

	driverId=getNumberInput("||\tEnter driver id: \n");

	Driver driver = driverStorer.getDriverById(driverId);

	std::cout << "\033[32m||\tEarned money by " << driver.getLogin() << ": " << orderStorer.getTotalMoney(driverId) << "\033[0m\n";
}

void AdminInterface::getTotalMileageAndWeightByCar()
{
	std::string carNumber;

	std::cout << "||\tEnter car number\n";
	std::cin >> carNumber;

	carStorer.getCarByNumber(carNumber);

	std::pair<int, int> mileageAndWeight = carStorer.getCarTotalMileageAndMass(carNumber);

	std::cout << "\033[32m||\tMileage: " << mileageAndWeight.first << "; Cargo weight: " << mileageAndWeight.second << "\033[0m\n";
}

void AdminInterface::getOrdersListByDriver()
{
	int driverId;

	driverId=getNumberInput("||\tEnter driver id: \n");

	std::vector<Order> orders = driverStorer.getOrdersByDriverAndPeriod(driverId);

	for (Order order : orders)
	{
		std::cout << "\033[32m" << order.toString() << "||\n"
				  << "\033[0m";
	}
}

void AdminInterface::getAllInfoByDriverWithLeastOrders()
{
	std::pair<Driver, double> worstDriverWithMoney = driverStorer.getDriverWithMinimumTripsAndMoney();
	std::cout << "\033[32m" << worstDriverWithMoney.first.toString() << "||\tMoney earned: " << worstDriverWithMoney.second << "\033[0m\n";
}

void AdminInterface::getMoneyByEachDriver()
{
	std::vector<Driver> drivers = driverStorer.getDrivers();

	for (Driver driver : drivers)
	{
		std::cout << "\033[32m||\tDriver " << driver.getLogin() << " earned " << orderStorer.getTotalMoney(driver.getId()) << " money\033[0m\n";
	}
}

void AdminInterface::getAllInfoByCarWithHighestMileage()
{
	std::cout << "\033[32m"
			  << "||\tInfo about car with highest mileage:\n"
			  << carStorer.getCarWithMaximumMileage().toString() << "\033[0m";
}

void AdminInterface::addDriver()
{
	std::string login;
	std::string password;
	std::string name;
	std::string category;
	int day, month, year;
	int birthYear;
	std::string address;

	while (true)
	{
		std::string quitStr;

		std::cout << "||\tEnter loaddDrivergin: ";
		std::cin >> login;

		if (!Validator::isValidLogin(login))
		{
			std::cout << "\033[31m"
					  << "||\tLogin is not valid\n"
					  << "||\tLogin should contain only letters, digits or _\n"
					  << "\033[0m";
			continue;
		}

		if (auth.userExists(login))
		{
			std::cout << "\033[31m"
					  << "||\tUser with login " << login << " already exists\n"
					  << "\033[0m";

			std::cout << "\033[31m"
					  << "||\tIf you want to quit, type \"q\". Otherwise - anything else\n"
					  << "\033[0m";

			std::cin >> quitStr;

			trim(quitStr);
			if (tryQuit(quitStr))
			{
				return;
			}

			continue;
		}

		std::cout << "||\tEnter password: ";
		std::cin >> password;

		if (password.empty())
		{
			std::cout << "\033[31m"
					  << "||\tPassword is empty\n"
					  << "\033[0m";
			continue;
		}

		break;
	}

	while (true)
	{
		std::string quitStr;

		std::cout << "||\tEnter name: ";
		std::cin >> name;
		std::cout << "||\tEnter category: ";
		std::cin >> category;
		std::cout << "||\tEnter start work date:\n";
		day = getNumberInput("||\tEnter day:");
		month = getNumberInput("||\tEnter month:");
		year = getNumberInput("||\tEnter year:");
		birthYear = getNumberInput("||\tEnter birth year:");
		std::cout << "||\tEnter address: ";
		std::cin >> address;

		try
		{
			Driver driver = Driver(-1, login, name, category, DatabaseHelper::dateToSec(year, month, day), birthYear, address);

			auth.addUser(login, password, UserType::DRIVER);
			driverStorer.addDriver(driver);

			std::cout << "\033[32m"
					  << "||\tDriver successfully added!\n"
					  << "\033[0m";

			return;
		}
		catch (const std::exception &e)
		{
			std::cout << "\033[31m"
					  << "||\t" << e.what() << '\n'
					  << "\033[0m";

			std::cout << "\033[31m"
					  << "||\tIf you want to quit, type \"q\". Otherwise - anything else\n"
					  << "\033[0m";

			std::cin >> quitStr;

			trim(quitStr);
			if (tryQuit(quitStr))
			{
				return;
			}

			continue;
		}
	}
}

void AdminInterface::addCar()
{
	std::string number;
	std::string brand;
	std::string model;
	int purchaseMileage;
	int carryingCapacity;

	std::cout << "||\tEnter number: ";
	std::cin >> number;
	std::cout << "||\tEnter brand: ";
	std::cin >> brand;
	std::cout << "||\tEnter model: ";
	std::cin >> model;
	purchaseMileage = getNumberInput("||\tEnter purchase mileage: ");
	carryingCapacity = getNumberInput("||\tEnter carrying capacity: ");

	try
	{
		Car car = Car(number, brand, model,carryingCapacity,purchaseMileage);
		carStorer.addCar(car);

		std::cout << "\033[32m"
				  << "||\tCar successfully added"
				  << "\033[0m" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "\033[31m"
				  << "||\t Exeption: " << e.what() << "\033[0m" << std::endl;
	}
}

void AdminInterface::addOrder()
{
	long date;
	int day, month, year;
	int driverId;
	std::string carNumber;
	int mileage;
	int cargoWeight;
	int cost;

	std::cout << "||\tEnter date:\n";
	day = getNumberInput("||\tEnter day:");
	month = getNumberInput("||\tEnter month:");
	year = getNumberInput("||\tEnter year:");
    driverId = getNumberInput("||\tEnter driver id: ");
	std::cout << "||\tEnter carNumber: ";
	std::cin >> carNumber;
	mileage = getNumberInput("||\tEnter mileage: ");
	cargoWeight = getNumberInput("||\tEnter cargo weight: ");
	cost = getNumberInput("||\tEnter cost: ");

	date = DatabaseHelper::dateToSec(year, month, day);
	Car car = carStorer.getCarByNumber(carNumber);
	if (car.getCarryingCapacity() < cargoWeight)
	{
		std::cout << "\033[32m"
				  << "||\tIt's impossible to deliver cargo with weight " << cargoWeight << " by car with carrying capacity " << car.getCarryingCapacity()
				  << "\033[0m" << std::endl;
		return;
	}

	try
	{
		Order order = Order(-1, date, driverId, carNumber, mileage, cargoWeight, cost);
		orderStorer.addOrder(order);

		std::cout << "\033[32m"
				  << "||\tOrder successfully added!"
				  << "\033[0m" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "\033[31m"
				  << "||\t Exeption: " << e.what() << "\033[0m" << std::endl;
	}
}

void AdminInterface::getListOfDrivers()
{
	std::vector<Driver> drivers = driverStorer.getDrivers();

	for (Driver driver : drivers)
	{
		std::cout << "\033[32m" << driver.toString() << "||\n"
				  << "\033[0m";
	}
}

void AdminInterface::getListOfCars()
{
	std::vector<Car> cars = carStorer.getAllCars();

	for (Car car : cars)
	{
		std::cout << "\033[32m" << car.toString() << "||\n"
				  << "\033[0m";
	}
}

void AdminInterface::getListOfOrders()
{
	std::vector<Order> orders = orderStorer.getAllOrders();

	for (Order order : orders)
	{
		std::cout << "\033[32m" << order.toString() << "||\n"
				  << "\033[0m";
	}
}