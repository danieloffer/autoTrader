/**
 * logger.hpp
 * this module's purpose is to make the SingleLogger module into a singleton
 **/

#ifndef LOGGER
#define LOGGER

#include <string>
#include <single_logger.hpp>

using namespace std;

namespace autoTrader
{

class Logger
{
public:
    /*
    *Writes a log message in the log file
    *param msg - the message to be written
    *param fileName - the file the msg originated from
    *param funcName - the function the msg originated from
    *param lineNum - the line the msg originated from
    */
    void log(string msg,string fileName, string funcName, int lineNum);

    /*
    *Returns an instance of a SingleLogger. The logger functionality is meant to operate with a single logger
    */
    static SingleLogger *getInstance();
private:
    ~Logger();
    static void cleanup();
    static SingleLogger *s_loggerInstance;
};

}//namespace autoTrader

#endif //LOGGER