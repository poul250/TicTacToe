#include "Log.h"

Log::Log()
{}

Log::~Log()
{}

void Log::operator()(std::string msg)
{
    std::cout << msg << std::endl;
}
