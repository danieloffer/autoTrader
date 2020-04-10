/**
 * control_server.cpp
 **/

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <string.h>
#include <control_server.hpp>
#include <client_server_types.hpp>

using namespace std;

namespace autoTrader
{
    ControlServer::ControlServer() : log(Logger::getInstance())
    {
        struct sockaddr_in server_addr = {0};
        struct sockaddr_storage client_addr = {0};
        
        currentUiScreen = {"Please enter your selection:\n1:Buy\n2:Sell\n3:Settings\0", INT};
        tcp_fd = socket(AF_INET, SOCK_STREAM, 0);

        log->LOG("ControlServer ctor - fd = " + to_string(tcp_fd));

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
        close(tcp_fd);
        close(sock_new);
    }

    void ControlServer::presentUi()
    {   
        log->LOG("ControlServer::presentUi");

        if (-1 == write(sock_new, &currentUiScreen.expectedInputType, sizeof(currentUiScreen.expectedInputType)))
        {
            log->LOG("ControlServer::presentUi - Error writing to socket");
        }
        if (-1 == write(sock_new, currentUiScreen.uiMessage, strlen(currentUiScreen.uiMessage) + 1))
        {
            log->LOG("ControlServer::presentUi - Error writing to socket");
        }
    }

    void ControlServer::getUserInput()
    {
        size_t bytesToRead = 0;
        void *userInput = NULL;

        log->LOG("ControlServer::getUserInput");

        if (INT == currentUiScreen.expectedInputType)
        {
            int userInputInt = 0;

            bytesToRead = sizeof(int);
            userInput = calloc(bytesToRead, sizeof(char));

            if (!userInput)
            {
                log->LOG("ControlServer::getUserInput - Error allocation buffer");
            }
            if (-1 == read(sock_new, &userInputInt, bytesToRead))
            {
                log->LOG("ControlServer::getUserInput - Error reading from socket");
            }

            log->LOG("ControlServer::getUserInput - user pressed: " + to_string(userInputInt));
        }
        else
        {
            bytesToRead = MAX_MSG_LEN;
            userInput = calloc(bytesToRead, sizeof(char));

            if (!userInput)
            {
                log->LOG("ControlServer::getUserInput - Error allocation buffer");
            }
            if (-1 == read(sock_new, &userInput, bytesToRead))
            {
                log->LOG("ControlServer::getUserInput - Error reading from socket");
            }
        }

        free(userInput);
    }

}//namespace autoTrader