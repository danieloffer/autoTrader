/**
 * error_codes.hpp
 * this module's purpose is to detail the possible error types
 **/

#ifndef ERROR_CODES
#define ERROR_CODES

namespace autoTrader
{
enum E_ErrorCodes 
{
    NO_ERR = 0,
    SERVER_CONNECTION_ERR = 1,
    SERVER_SOCKET_WRITE_ERR = 2,
    SERVER_SOCKET_READ_ERR = 3,
    SERVER_ALLOCATION_ERR = 4,

    CLIENT_CONNECTION_ERR = 101,
    CLIENT_SOCKET_WRITE_ERR = 102,
    CLIENT_SOCKET_READ_ERR = 103,
    CLIENT_ALLOCATION_ERR = 104,
};

}//namespace autoTrader

#endif //ERROR_CODES