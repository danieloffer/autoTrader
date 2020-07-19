/**
 * server.hpp
 * this module's purpose is to make the ControlServer module into a singleton
 **/

#ifndef SERVER
#define SERVER

#include <control_server.hpp>

using namespace std;

namespace autoTrader
{

class Server
{
public:
    /*
    *Returns a pointer to a ControlServer instance. The ControlServer is meant to be a singleton
    */
    static ControlServer *getInstance();
private:
    ~Server();
    static void cleanup();
    static ControlServer *s_serverInstance;
};

}//namespace autoTrader

#endif //SERVER