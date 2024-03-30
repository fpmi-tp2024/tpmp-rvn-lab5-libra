#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <iostream>
#include "../include/UtilFunctions.h"

using std::string;
using std::cin;
using std::cout;

void startAdmin();
bool tryLogInAdmin(const string&, const string&);

#endif