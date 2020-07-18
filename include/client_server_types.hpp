/**
 * client_server_types.hpp
 * this module's purpose is to present the client-server api, The data types they exchange.
 **/

#ifndef CLIENT_SERVER_TYPES
#define CLIENT_SERVER_TYPES

using namespace std;

#define SERVER_PORT_NUM 1234 //choose which port to connect to. The server must openthe same port
#define MAX_MSG_LEN 1024
#define MAX_DATA_LEN 2048

namespace autoTrader
{
    // The type of input the user is expected to send
    enum E_InputType
    {
        INT = 0,
        STR = 1
    };
    
    //A struct that represents the UI the server passes to the client. 
    //It contains a message for the client to present to the user and the type of data the server is watinf for
    struct ClientServerUi
    {
        char *uiMessage;
        E_InputType expectedInputType;
    };
}//namespace autoTrader

#endif //CLIENT_SERVER_TYPES