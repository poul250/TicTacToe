#pragma once
#include <iostream>
#include <string>

class Log
{
public:
    Log();
    ~Log();
    void operator()(std::string msg);
};
