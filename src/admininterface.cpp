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
		std::cout << "\033[31m" << "||\tUsername or password are not valid. Try again\n";
		std::cout << "||\tIf you want to quit, type \"q\". Otherwise - anything else\n" << "\033[0m";
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

	std::cout << "\033[32m" << std::endl << "||\tSuccessfully logged in\n" << "\033[0m";

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
				try {
				(this->*(it->second))();
				}
				catch (const std::exception& e) {
    				std::cout << "\033[31m" << "Exception: " << e.what() << "\033[0m" << std::endl;
				}
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

	std::cout << "\033[32m||\tTotal number of completed orders:" << orderStorer.getTotalNumberOfOrders(driverId) << "\033[0m\n";
}

void AdminInterface::getTotalWeightByDriver()
{
	int driverId;

	std::cout << "||\tEnter driver id\n";
	std::cin >> driverId;

	Driver driver = driverStorer.getDriverById(driverId);

	std::cout << "\033[32m||\tTotal weight delivered by driver " <<driver.getLogin()<<" : "<< orderStorer.getTotalCargoMass(driverId) << "\033[0m\n\n";
}

void AdminInterface::getTotalMoneyByDriver()
{
	int driverId;

	std::cout << "||\tEnter driver id\n";
	std::cin >> driverId;

	Driver driver = driverStorer.getDriverById(driverId);

	std::cout << "\033[32m||\tEarned money by " <<driver.getLogin()<<" : "<< orderStorer.getTotalMoney(driverId) << "\033[0m\n";
}

void AdminInterface::getTotalMileageAndWeightByCar()
{
	std::string carNumber;

	std::cout << "||\tEnter car number\n";
	std::cin >> carNumber;

	std::pair<int, int> mileageAndWeight = carStorer.getCarTotalMileageAndMass(carNumber);
	
	std::cout << "\033[32m||\tMileage: " << mileageAndWeight.first << " ; Cargo weight: " << mileageAndWeight.second << "\033[0m\n";
}

void AdminInterface::getOrdersListByDriver()
{
	int driverId;

	std::cout << "||\tEnter driver id\n";
	std::cin >> driverId;

	std::vector<Order> orders = driverStorer.getOrdersByDriverAndPeriod(driverId, 0, LONG_MAX); //TODO: Maxim -- fix time intervals
	
	for (Order order : orders)
	{
		std::cout << "\033[32m" << order.toString() << "\033[0m";
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
	std::cout << "\033[32mInfo about car with highest mileage:\n"<<carStorer.getCarWithMaximumMileage().toString()<<"\033[0m\n";
}

void AdminInterface::addDriver()
{
    std::string login;
    std::string name;
    std::string category;
    long startWorkDate;
	int day, month, year;
    int birthYear;
    std::string address;
	std::string password;

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

	Driver driver = Driver(-1,login, name, category, startWorkDate, birthYear, address);
	driverStorer.addDriver(driver, password);
	std::cout << "\033[32mDriver successfully added\033[0m" << std::endl;
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
	std::cout << "\033[32mCar successfully added\033[0m" << std::endl;
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

	std::cout << "||\tEnter date(DD MM YYYY): ";
	std::cin >> day >> month >> year;
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

	date = DatabaseHelper::dateToSec(year, month, day);
	Car car = carStorer.getCarByNumber(carNumber);
	if (car.getCarryingCapacity()< cargoWeight){
		std::cout << "\033[32mIt's impossible to deliver cargo with weight "<<cargoWeight<<" by car with carrying capacity "<<car.getCarryingCapacity()<<"\033[0m"<<std::endl;
		return;
	}
	Order order = Order(-1,date, driverId, carNumber, mileage, cargoWeight, cost);
	orderStorer.addOrder(order);
	std::cout << "\033[32mOrder successfully added\033[0m" << std::endl;
}