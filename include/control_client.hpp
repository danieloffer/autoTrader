/**
 * control_client.hpp
 * this module's purpose is to serve as the programm's front end to control a remote running program
 **/

#ifndef CONTROL_CLIENT
#define CONTROL_CLIENT

#include <string>
#include <client_server_types.hpp>

#define SERVER_ADDR "192.168.68.110"

using namespace std;

namespace autoTrader
{

class ControlClient
{
public:
    ControlClient();
    ~ControlClient();

    int sendUserInput(int userSelection);
    int sendUserInput(string userSelection);
    ClientServerUi getNewUi();
private:
    int sock_fd;
};

}//namespace autoTrader

#endif //CONTROL_CLIENT