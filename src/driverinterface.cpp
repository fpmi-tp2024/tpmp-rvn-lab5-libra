#include "../include/driverinterface.h"

std::map<int, void (*)()> commands = {
	{1, handleSomeAction1},
	{2, handleSomeAction2},
	// TODO: Add more functions
};

void startDriver()
{
	string uName;
	string password;
	string quitStr;

	cout << "||\tYou selected Driver account\n";
	cout << "||\tEnter Username and Password to proceed\n";
	cout << "||\tUsername: ";
	std::getline(cin, uName);
	cout << "||\tPassword: ";
	std::getline(cin, password);
	trim(uName);
	trim(password);

	while (!tryLogInDriver(uName, password))
	{
		cout << "||\tUsername or password are not valid. Try again\n";
		cout << "||\tIf you want to quit, type \"q\"\n";
		std::getline(cin, quitStr);
		trim(quitStr);
		if (tryQuit(quitStr))
		{
			return;
		}
		cout << "||\tUsername: ";
		std::getline(cin, uName);
		cout << "||\tPassword: ";
		std::getline(cin, password);
		trim(uName);
		trim(password);
	}

	cout << "||\tSuccessfully logged in\n";

	string input;
	int option;

	// TODO: Add more operations
	string commandsList = "||\tSelect operation:\n"
						  "||\t1: <Some_Operation>\n"
						  "||\t2: <Some_Operation>\n"
						  "||\n"
						  "||\tOr type \"q\" to quit\n";

	string invalidInputError = "||\tYour input is not valid. Try again\n";

	while (true)
	{
		cout << commandsList;

		std::getline(cin, input);
		trim(input);

		if (tryQuit(input))
		{
			return;
		}

		if (!tryParseString(input, option))
		{
			cout << invalidInputError;
		}
		else
		{
			auto it = commands.find(option);

			if (it != commands.end())
			{
				it->second();
			}
			else
			{
				cout << invalidInputError;
			}
		}
	}
}

bool tryLogInDriver(const string &uName, const string &password)
{
	// TODO: Implement LogIn System
	return true;
}

void handleSomeAction1()
{
	// TODO: Replace
	cout << "First Action\n";
}

void handleSomeAction2()
{
	// TODO: Replace
	cout << "Second Action\n";
}