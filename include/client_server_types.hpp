/**
 * client_server_types.hpp
 * this module's purpose is to present the client-server api, The data types they exchange.
 **/

#ifndef CLIENT_SERVER_TYPES
#define CLIENT_SERVER_TYPES

using namespace std;

#define SERVER_PORT_NUM 1234 //choose which port to connect to. The server must open the same port
#define MAX_MSG_LEN 1024
#define MAX_DATA_LEN 2048

namespace autoTrader
{
    //communication type to start
    enum E_CommType
    {
        UI_TRANSFER = 0,
        STOCK_DATA_TRANSFER = 1,
    };

    // The type of input the user is expected to send
    enum E_InputType
    {
        INT = 0,
        STR = 1
    };

    /*
    The first 2 vars are the header which the server 
    and client send to each other 
    the data to be transfared is at the end of the header as a 
    "Stretchy Buffer"
    */
    struct ClientServerComm
    {
        E_CommType commType;
        size_t messageLen;
        char *dataToTransfer;
    };

    struct ClientServerUi
    {
        char *msg;
        E_InputType expectedInput;
    };
}//namespace autoTrader

#endif //CLIENT_SERVER_TYPES