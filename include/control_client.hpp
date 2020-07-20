/**
 * control_client.hpp
 * this module's purpose is to serve as the programm's front end to control a remote running program
 **/

#ifndef CONTROL_CLIENT
#define CONTROL_CLIENT

#include <string>
#include <client_server_types.hpp>

#define SERVER_ADDR "192.168.14.197" // The IP address of the server. (might change, need to find a way to dynamically find addr or make permenant)

using namespace std;

namespace autoTrader
{

class ControlClient
{
public:
    /*
    *ControlClient Ctor
    */
    ControlClient() throw();
    /*
    *ControlClient Dtor
    */
    ~ControlClient();

    /*
    *Sends the user selection to the server
    *param userSelection - the user selection (int)
    *Returns 0 on success
    */
    int sendUserInput(int userSelection) throw();

    /*
    *Sends the user selection to the server
    *param userSelection - the user selection (string)
    *Returns 0 on success
    */
    int sendUserInput(string userSelection) throw();

    /*
    *Gets a new ClientServerUi from the server. A blocking function, waits for the server to send the new UI
    *Returns ClientServerUi on success On failure, the struct will contain NULL uiMessage
    */
    ClientServerUi getNewUi() throw();

    /*
    *Reads data from the server. A blocking function, waits for the server
    *param buf - a pre-allocated buffer to put the incoming data from the server into
    */
    void readDataFromServer(char *buf) throw();
private:
    int sock_fd;
};

}//namespace autoTrader

#endif //CONTROL_CLIENT