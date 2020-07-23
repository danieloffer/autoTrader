/**
 * control_server.hpp
 * this module's purpose is to serve as the programm's control unit on remote site which communicates with local client
 **/

#ifndef CONTROL_SERVER
#define CONTROL_SERVER

#include <logger.hpp>
#include <client_server_types.hpp>

using namespace std;

namespace autoTrader
{
class ControlServer
{
public:

    /*
    *ControlServer Ctor
    */
    ControlServer() throw();

    /*
    *ControlServer Dtor
    */
    ~ControlServer();

    /*
    *Receive and process user input sent from the ControlClient. 
    *A blocking function, waits for the client
    */
    void getAndProcessUserInput() throw();

    /*
    *Sends data to the client
    *param data - the data to sent to the client
    */
    void sendDataToClient(ClientServerComm *commHeadera) throw();

    /*
    *Sends data to the client
    */
    void sendDataToClient() throw();

    /*
    *Sets the data in commHeader
    */
    void setData(const char *data);

private:
    SingleLogger *log;
    int currentScreen;
    int sock_new;
    int tcp_fd;
    ClientServerComm *commHeader;
};

}//namespace autoTrader

#endif //CONTROL_SERVER