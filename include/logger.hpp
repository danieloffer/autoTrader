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
    void log(string msg,string fileName, string funcName, int lineNum);
    static SingleLogger *getInstance();
private:
    ~Logger();
    static void cleanup();
    static SingleLogger *s_loggerInstance;
};

}//namespace autoTrader

#endif //LOGGER