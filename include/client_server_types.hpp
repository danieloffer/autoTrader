/**
 * client_server_types.hpp
 * this module's purpose is to present the client-server api, The data types they exchange.
 **/

#ifndef CLIENT_SERVER_TYPES
#define CLIENT_SERVER_TYPES

using namespace std;

#define SERVER_PORT_NUM 1234
#define MAX_MSG_LEN 1024

namespace autoTrader
{
    enum E_InputType
    {
        INT = 0,
        STR = 1
    };
    
    struct ClientServerUi
    {
        char *uiMessage;
        E_InputType expectedInputType;
    };
}//namespace autoTrader

#endif //CLIENT_SERVER_TYPES