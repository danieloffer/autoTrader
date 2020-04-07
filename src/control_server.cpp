/**
 * control_server.cpp
 **/

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <control_server.hpp>
#include <client_server_types.hpp>

using namespace std;

namespace autoTrader
{
    ControlServer::ControlServer() : log(Logger::getInstance())
    {
        struct sockaddr_in server_addr = {0};
        int tcp_fd = socket(AF_INET, SOCK_STREAM, 0);
        int sock_new;
        struct sockaddr_storage client_addr = {0};

        log->LOG("ControlServer ctor - fd = " + tcp_fd);

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT_NUM);
        server_addr.sin_addr.s_addr = INADDR_ANY;

        if (tcp_fd == -1)
        {
            perror("socket: ");
        }

        if (bind(tcp_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        {
            perror("bind tcp: ");
            close(tcp_fd);
        }

        if (listen(tcp_fd, 5) == -1)
        {
            perror("listen: ");
            close(tcp_fd);
        }

        socklen_t len = sizeof(client_addr);
        sock_new = accept(tcp_fd, (struct sockaddr *)&client_addr, &len);
    }

    ControlServer::~ControlServer()
    {
        log->LOG("ControlServer dtor");
    }

    void ControlServer::presentUi()
    {
        log->LOG("ControlServer::presentUi");
    }

    void ControlServer::getUserInput()
    {
        log->LOG("ControlServer::getUserInput");
    }

}//namespace autoTrader