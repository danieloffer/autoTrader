/**
 * logger.hpp
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
    SingleLogger *operator->();
private:
    ~Logger();
    static void cleanup();
    static SingleLogger *s_loggerInstance;
};

}//namespace autoTrader

#endif //LOGGER