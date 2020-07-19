/**
 * single_logger.hpp
 * this module's purpose is to log everything that happens in the other modules to a log file
 **/

#ifndef SINGLE_LOGGER
#define SINGLE_LOGGER

#include <string>
#include <fstream>

using namespace std;

/*
*The "LOG" macro is used to save the user from inputting all the params every time 
*by taking then automatically using the "FILE" "FUNCTION" and "LINE" macros
*The user of te logger just needs to pass the desired msg
*/
#define LOG(x) log((x), string(__FILE__), string(__FUNCTION__), __LINE__)
#define LOG_FILE_NAME "./autoTrader.log" //The file all log msg are written to

namespace autoTrader
{

class SingleLogger
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
    *SingleLogger Ctor
    */
    SingleLogger();

    /*
    *SingleLogger Dtor
    */
    ~SingleLogger();
private:
    ofstream logFile;
};

}//namespace autoTrader

#endif //SINGLE_LOGGER