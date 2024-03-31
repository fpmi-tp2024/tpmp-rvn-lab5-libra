#include "../include/menuinterface.h"

void startMenu()
{
	int option;
	string input;

	cout << "||\tSelect account type:\n";
	cout << "||\t1: Admin\n";
	cout << "||\t2: Driver\n";
	cout << "||\n";
	cout << "||\tOr type \"q\" to quit\n";
	std::getline(cin, input);
	trim(input);

	while (!tryParseString(input, option) || (option != 1 && option != 2))
	{
		if (tryQuit(input))
		{
			return;
		}

		cout << "||\tYour input is not valid. Try again\n";
		std::getline(cin, input);
		trim(input);
	}

	if (option == 1)
	{
		startAdmin();
	}
	else
	{
		startDriver();
	}
}