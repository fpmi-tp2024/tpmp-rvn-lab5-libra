#ifndef DRIVERINTERFACE_H
#define DRIVERINTERFACE_H

#include <string>
#include <iostream>
#include "utilfuntions.h"

using std::cin;
using std::cout;
using std::string;

void startDriver();
bool tryLogInDriver(const string &, const string &);

#endif