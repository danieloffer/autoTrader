/**
 * server.cpp
 **/

#include <server.hpp>

using namespace std;

namespace autoTrader
{
    ControlServer *Server::s_serverInstance = NULL;
    
    ControlServer *Server::getInstance()
    {
        if (!s_serverInstance)
        {
            s_serverInstance = new ControlServer();
			std::atexit(&cleanup);
        }

        return s_serverInstance;
    }

    Server::~Server()
    {

    }

    void Server::cleanup()
    {
        delete s_serverInstance;
    }
}//namespace autoTrader