#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include <string>
#include <iostream>
#include "driverinterface.h"

using std::cin;
using std::cout;
using std::string;

void startAdmin();
bool tryLogInAdmin(const string &, const string &);

#endif