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
    *Reads data from the server based on the header and handles based on commType.
    *Blocking function
    */
    void recvAndHandleDataFromServer() throw();

    /*
    *Reads user input and sends it to the server.
    *Returns 1 as long as user doesn't enter 0 to exit
    */
    int getAndsendUserDataToServer() throw();

    /*
    *Returns 1 if there is another transmission from the server to process, 0 otherwise
    */
    int isMoreToRead();
private:
    int sock_fd;
    ClientServerComm *commHeader;
};

}//namespace autoTrader

#endif //CONTROL_CLIENT