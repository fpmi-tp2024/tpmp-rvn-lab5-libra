#include "../include/utilfuntions.h"

void trim(string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch)
                                        { return !std::isspace(ch); }));

    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch)
                           { return !std::isspace(ch); })
                  .base(),
              str.end());
}

bool tryParseString(const string &str, int &parsedVal)
{
    std::istringstream iss(str);
    int val = 0;

    iss >> val;

    if (iss.eof() && !iss.fail())
    {
        parsedVal = val;
        return true;
    }
    else
    {
        parsedVal = 0;
        return false;
    }
}

bool tryQuit(const string &str)
{
    if (str == "q")
    {
        // TODO: process quit
        return true;
    }
    else
    {
        return false;
    }
}