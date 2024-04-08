#ifndef DRIVERINTERFACE_H
#define DRIVERINTERFACE_H

#include <string>
#include <iostream>
#include <map>
#include "utilfuntions.h"

using std::cin;
using std::cout;
using std::string;

void startDriver();
bool tryLogInDriver(const string &, const string &);

void handleSomeAction1();
void handleSomeAction2();

#endif