/*
* single_logger.cpp
*/

#include <logger.hpp>
#include <iostream>
#include <time.h>

using namespace std;

namespace autoTrader
{
	static string getCurrentTime()
	{
		time_t now = time(NULL);
        struct tm *dt = localtime(&now);
        char currTime[200] = {0};

        strftime(currTime, 200, "%a %m/%d/%y %H:%M:%S " , dt);

		return string(currTime);
	}

    void SingleLogger::log(string msg,string fileName, string funcName, int lineNum)
    { 
        logFile << getCurrentTime() <<  fileName << ":" << lineNum << " - " << msg << endl;
    }

    SingleLogger::SingleLogger()
    {
        logFile.open(LOG_FILE_NAME, ios::out | ios::ate);
		if (!logFile)
		{
			cout << "Failed to open " << LOG_FILE_NAME << " for writing" << endl;
		}
		else
		{
			LOG("***Logger Initialized***");
		}
		
    }

    SingleLogger::~SingleLogger()
    {
        LOG("***Logger destroyed***");
		logFile.close();
    }
    
}//namespace autoTrader