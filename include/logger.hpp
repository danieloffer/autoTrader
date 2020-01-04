/**
 * Logger.hpp
 **/

#ifndef LOGGER
#define LOGGER

#include <string>

using namespace std;

#define LOG(x) log((x), string(__FILE__), string(__FUNCTION__), __LINE__)

namespace autoTrader
{

class Logger
{
public:
    void log(string msg,string fileName, string funcName, int lineNum);
    static Logger *getInstance();
    ~Logger();
private:
    Logger();
    static Logger *s_loggerInstance;
};

}//namespace autoTrader

#endif //LOGGER