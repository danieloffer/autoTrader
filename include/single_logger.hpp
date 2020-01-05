/**
 * single_logger.hpp
 **/

#ifndef SINGLE_LOGGER
#define SINGLE_LOGGER

#include <string>
#include <fstream>

using namespace std;

#define LOG(x) log((x), string(__FILE__), string(__FUNCTION__), __LINE__)
#define LOG_FILE_NAME "./autoTrader.log"

namespace autoTrader
{

class SingleLogger
{
public:
    void log(string msg,string fileName, string funcName, int lineNum);
    SingleLogger();
    ~SingleLogger();
private:
    ofstream logFile;
};

}//namespace autoTrader

#endif //SINGLE_LOGGER