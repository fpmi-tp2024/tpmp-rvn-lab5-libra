#include "../include/admin.h"

void startAdmin()
{
	string uName;
	string password;
	string quitStr;

	cout << "||\tYou selected Admin account\n";
	cout << "||\tEnter Username and Password to proceed\n";
	cout << "||\tUsername: ";
	std::getline(cin, uName);
	cout << "||\tPassword: ";
	std::getline(cin, password);
	trim(uName);
	trim(password);

	while (!tryLogInAdmin(uName, password))
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

	while (true)
	{
		cout << "||\tSelect operation:\n";
		cout << "||\t1: <Some_Operation>\n";
		// TODO: Add more operations
		cout << "||\n";
		cout << "||\tOr type \"q\" to quit\n";
		std::getline(cin, input);
		trim(input);

		if (tryQuit(input))
		{
			return;
		}

		if (!tryParseString(input, option))
		{
			cout << "||\tYour input is not valid. Try again\n";
		}
		else
		{
			switch (option)
			{
			case 1:
				// TODO: Add function
				break;

				// TODO: Add more functions

			default:
				cout << "||\tYour input is not valid. Try again\n";
				break;
			}
		}
	}
}

bool tryLogInAdmin(const string &uName, const string &password)
{
	// TODO: Implement LogIn System
	return true;
}
