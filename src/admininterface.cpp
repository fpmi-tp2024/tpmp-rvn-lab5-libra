#include "../include/admininterface.h"
#include "../config/config.hpp"

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
	};
}

AdminInterface::~AdminInterface() {}

void AdminInterface::run()
{
	std::string login;
	std::string password;
	std::string quitStr;

	std::cout << "||\tYou selected Admin account\n";
	std::cout << "||\tEnter Username and Password to proceed\n";
	std::cout << "||\tUsername: ";
	std::cin >> login;
	std::cout << "||\tPassword: ";
	std::cin >> password;
	trim(login);
	trim(password);

	while (!tryLogInAdmin(login, password))
	{
		std::cout << "||\tUsername or password are not valid. Try again\n";
		std::cout << "||\tIf you want to quit, type \"q\". Otherwise - anyhting else\n";
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
	}

	std::cout << "||\tSuccessfully logged in\n";

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
						  "||\n"
						  "||\tOr type \"q\" to quit\n";

	std::string invalidInputError = "||\tYour input is not valid. Try again\n";

	while (true)
	{
		std::cout << commandsList;

		std::cin >> input;
		trim(input);

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
				(this->*(it->second))();
			}
			else
			{
				std::cout << invalidInputError;
			}
		}
	}
}

bool AdminInterface::tryLogInAdmin(const std::string &login, const std::string &password)
{
	return Config::getString("admine_login") == login && 
		Config::getString("admine_password") == password;
		
}

void AdminInterface::getTotalOrdersByDriver()
{
	int driverId;

	std::cout << "||\tEnter driver id\n";
	std::cin >> driverId;

	Driver driver = driverStorer.getDriverById(driverId);

	std::cout << "||\t" << orderStorer.getTotalNumberOfOrders(driverId) << "\n";
}

void AdminInterface::getTotalWeightByDriver()
{
	int driverId;

	std::cout << "||\tEnter driver id\n";
	std::cin >> driverId;

	Driver driver = driverStorer.getDriverById(driverId);

	std::cout << "||\t" << orderStorer.getTotalCargoMass(driverId) << "\n";
}

void AdminInterface::getTotalMoneyByDriver()
{
	int driverId;

	std::cout << "||\tEnter driver id\n";
	std::cin >> driverId;

	Driver driver = driverStorer.getDriverById(driverId);

	std::cout << "||\t" << orderStorer.getTotalMoney(driverId) << "\n";
}

void AdminInterface::getTotalMileageAndWeightByCar()
{
	std::string carNumber;

	std::cout << "||\tEnter car number\n";
	std::cin >> carNumber;

	std::pair<int, int> mileageAndWeight = carStorer.getCarTotalMileageAndMass(carNumber);
	
	std::cout << "||\tMileage: " << mileageAndWeight.first << " ; Cargo weight: " << mileageAndWeight.second << "\n";
}

void AdminInterface::getOrdersListByDriver()
{
	int driverId;

	std::cout << "||\tEnter driver id\n";
	std::cin >> driverId;

	std::vector<Order> orders = driverStorer.getOrdersByDriverAndPeriod(driverId, 0, LONG_MAX); //TODO: Maxim -- fix time intervals
	
	for (Order order : orders)
	{
		std::cout << order.toString();
	}
}

void AdminInterface::getAllInfoByDriverWithLeastOrders()
{
	std::pair<Driver, double> worstDriverWithMoney = driverStorer.getDriverWithMinimumTripsAndMoney();
	std::cout << worstDriverWithMoney.first.toString() << "||\tMoney earned: " << worstDriverWithMoney.second << "\n";
}

void AdminInterface::getMoneyByEachDriver()
{
	std::vector<Driver> drivers = driverStorer.getDrivers();

	for (Driver driver : drivers)
	{
		std::cout << "||\tDriver " << driver.getName() << " earned " << orderStorer.getTotalMoney(driver.getId()) << " money\n";
	}
}

void AdminInterface::getAllInfoByCarWithHighestMileage()
{
	std::cout << carStorer.getCarWithMaximumMileage().toString();
}

void AdminInterface::addDriver()
{
	int id;
    std::string login;
    std::string name;
    std::string category;
    long startWorkDate;
	int day, month, year;
    int birthYear;
    std::string address;
	std::string password;

	std::cout << "||\tEnter id: ";
	std::cin >> id;
	std::cout << "||\tEnter login: ";
	std::cin >> login;
	std::cout << "||\tEnter name: ";
	std::cin >> name;
	std::cout << "||\tEnter category: ";
	std::cin >> category;
	std::cout << "||\tEnter date of registration(DD MM YYYY): ";
	std::cin >> day >> month >> year;
	startWorkDate = DatabaseHelper::dateToSec(year, month, day);
	std::cout << "||\tEnter birth year: ";
	std::cin >> birthYear;
	std::cout << "||\tEnter address: ";
	std::cin >> address;
	std::cout << "||\tEnter password: ";
	std::cin >> password;

	Driver driver = Driver(id, login, name, category, startWorkDate, birthYear, address);
	driverStorer.addDriver(driver, password);
	// TODO: something with password hash
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
	std::cout << "||\tEnter mileage: ";
	std::cin >> purchaseMileage;
	std::cout << "||\tEnter carrying capacity: ";
	std::cin >> carryingCapacity;

	Car car = Car(number, brand, model, purchaseMileage, carryingCapacity);
	carStorer.addCar(car);
}

void AdminInterface::addOrder()
{
	int id;
    long date;
	int day, month, year;
    int driverId;
    std::string carNumber;
    int mileage;
    int cargoWeight;
    int cost;

	std::cout << "||\tEnter id: ";
	std::cin >> id;
	std::cout << "||\tEnter date(DD MM YYYY): ";
	std::cin >> day >> month >> year;
	date = DatabaseHelper::dateToSec(year, month, day);
	std::cout << "||\tEnter driverId: ";
	std::cin >> driverId;
	std::cout << "||\tEnter carNumber: ";
	std::cin >> carNumber;
	std::cout << "||\tEnter mileage: ";
	std::cin >> mileage;
	std::cout << "||\tEnter cargoWeight: ";
	std::cin >> cargoWeight;
	std::cout << "||\tEnter cost: ";
	std::cin >> cost;

	Order order = Order(id, date, driverId, carNumber, mileage, cargoWeight, cost);
	orderStorer.addOrder(order);
}