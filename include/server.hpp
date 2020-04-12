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
    static ControlServer *getInstance();
private:
    ~Server();
    static void cleanup();
    static ControlServer *s_serverInstance;
};

}//namespace autoTrader

#endif //SERVER