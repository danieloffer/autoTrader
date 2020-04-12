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
    ControlServer();
    ~ControlServer();

    void presentUi();
    void processUserInput();
    void sendDataToClient(void *data);

private:
    SingleLogger *log;
    int currentScreen;
    int sock_new;
    int tcp_fd;
};

}//namespace autoTrader

#endif //CONTROL_SERVER