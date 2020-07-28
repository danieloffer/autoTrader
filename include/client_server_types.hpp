/**
 * client_server_types.hpp
 * this module's purpose is to present the client-server api, The data types they exchange.
 **/

#include <string.h>

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
        E_UI_TRANSFER = 0,
        E_STOCK_DATA_TRANSFER = 1,
        E_BUY = 2,
        E_SELL = 3,
    };

    // The type of input the user is expected to send
    enum E_InputType
    {
        E_INT = 0,
        E_STR = 1
    };

    /*
    The first 3 vars are the header which the server 
    and client send to each other 
    the data to be transfared is at the end of the header as a 
    "Stretchy Buffer"
    */
    struct ClientServerComm
    {
        E_CommType commType;
        size_t messageLen;
        int isMoreComm;
        char *dataToTransfer;

        void serialize(char *buf)
        {
            *reinterpret_cast<int*>(buf + offsetof(ClientServerComm, commType)) = commType;
            *reinterpret_cast<size_t*>(buf + offsetof(ClientServerComm, messageLen)) = messageLen;
            *reinterpret_cast<int*>(buf + offsetof(ClientServerComm, isMoreComm)) = isMoreComm;
            strcpy((buf + offsetof(ClientServerComm, dataToTransfer)), dataToTransfer);
        }
    }__attribute__((__packed__));

    struct ClientServerUi
    {
        char *msg;
        E_InputType expectedInput;
    };
}//namespace autoTrader

#endif //CLIENT_SERVER_TYPES