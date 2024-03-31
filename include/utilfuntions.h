#ifndef UTILFUNCTIONS_H
#define UTILFUNCTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;

void trim(string &);
bool tryParseString(const string &, int &);
bool tryQuit(const string &);

#endif