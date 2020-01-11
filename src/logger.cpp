/*
* logger.cpp
*/

#include <logger.hpp>
#include <iostream>
#include <time.h>

using namespace std;

namespace autoTrader
{
    SingleLogger *Logger::s_loggerInstance = NULL;

    void Logger::log(string msg,string fileName, string funcName, int lineNum)
    {
        s_loggerInstance->log(msg, fileName, funcName, lineNum);
    }

    SingleLogger *Logger::getInstance()
    {
        if (!s_loggerInstance)
        {
            s_loggerInstance = new SingleLogger();
			std::atexit(&cleanup);
        }

        return s_loggerInstance;
    }

    Logger::~Logger()
    {
		
    }

	void Logger::cleanup()
	{
		delete s_loggerInstance;
	}
    
}//namespace autoTrader