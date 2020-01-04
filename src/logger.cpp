/*
* Logger.cpp
*/

#include <logger.hpp>
#include <iostream>
#include <time.h>

using namespace std;

namespace autoTrader
{
    Logger *Logger::s_loggerInstance = NULL;

    void Logger::log(string msg,string fileName, string funcName, int lineNum)
    {
        time_t now = time(NULL);
        struct tm *dt = localtime(&now);
        char currTime[200] = {0};

        strftime(currTime, 200, "%a %m/%d/%y %H:%M:%S " , dt);
        cout << currTime <<  fileName << ":" << lineNum << " - " << msg << endl;
    }

    Logger *Logger::getInstance()
    {
        if (!s_loggerInstance)
        {
            s_loggerInstance = new Logger();
        }

        return s_loggerInstance;
    }

    Logger::Logger()
    {

    }

    Logger::~Logger()
    {

    }
    
}//namespace autoTrader