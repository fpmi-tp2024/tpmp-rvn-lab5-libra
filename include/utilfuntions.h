#ifndef UTILFUNCTIONS_H
#define UTILFUNCTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

void trim(std::string &);
bool tryParseString(const std::string &, int &);
bool tryQuit(const std::string &);

#endif