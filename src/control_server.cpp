/**
 * control_server.cpp
 **/

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <string.h>
#include <iostream>
#include <control_server.hpp>
#include <client_server_types.hpp>
#include <server_operations.hpp>
#include <exception_types.hpp>

using namespace std;

namespace autoTrader
{
    ControlServer::ControlServer() throw(): log(Logger::getInstance()), currentScreen(0)
    {
        struct sockaddr_in server_addr = {0};
        struct sockaddr_storage client_addr = {0};
        
        tcp_fd = socket(AF_INET, SOCK_STREAM, 0);

        log->LOG("ControlServer ctor - fd = " + to_string(tcp_fd));

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT_NUM);
        server_addr.sin_addr.s_addr = INADDR_ANY;

        if (tcp_fd == -1)
        {
            perror("socket: ");
            throw SERVER_EXCEPTION(SERVER_CONNECTION_ERR);
        }

        if (bind(tcp_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        {
            perror("bind tcp: ");
            close(tcp_fd);
            throw SERVER_EXCEPTION(SERVER_CONNECTION_ERR);
        }

        if (listen(tcp_fd, 5) == -1)
        {
            perror("listen: ");
            close(tcp_fd);
            throw SERVER_EXCEPTION(SERVER_CONNECTION_ERR);
        }

        socklen_t len = sizeof(client_addr);
        sock_new = accept(tcp_fd, (struct sockaddr *)&client_addr, &len);

        commHeader = static_cast<ClientServerComm*>(calloc(sizeof(ClientServerComm), sizeof(char)));
        if (!commHeader)
        {
            cout << "Error allocating memory" << endl;
        }

        commHeader->commType = UI_TRANSFER;

        commHeader->dataToTransfer = static_cast<char*>(calloc(strlen(screens->uiScreen.msg) + 1,
                                        sizeof(char)));
        if (!commHeader->dataToTransfer)
        {
            throw SERVER_EXCEPTION(SERVER_ALLOCATION_ERR);
        }
        strcpy(commHeader->dataToTransfer, screens->uiScreen.msg);
        commHeader->messageLen = strlen(commHeader->dataToTransfer);
    }

    ControlServer::~ControlServer()
    {
        log->LOG("ControlServer dtor");
        close(tcp_fd);
        close(sock_new);

        if (commHeader)
        {
            if (commHeader->dataToTransfer)
            {
                free(commHeader->dataToTransfer);
            }

            free(commHeader);
        }
    }

    void static processUserInput(ClientServerComm *commHeader, int *currentScreen, int sockFd)
    {
        cout << "processUserInput" << endl;
        cout << "Received user input = " << commHeader->dataToTransfer << endl;

        if (INT == screens->uiScreen.expectedInput)
        {
            int intUserInput = *(reinterpret_cast<int*>(commHeader->dataToTransfer));
            *currentScreen = screens->actions[*currentScreen](&intUserInput);
        }
        else if(STR == screens->uiScreen.expectedInput)
        {
            *currentScreen = screens->actions[*currentScreen](commHeader->dataToTransfer);
        }


        if (commHeader->dataToTransfer)
        {
            free(commHeader->dataToTransfer);
            commHeader->dataToTransfer = NULL;
        }
        commHeader->messageLen = strlen(screens->uiScreen.msg);
        commHeader->dataToTransfer = static_cast<char*>(calloc(commHeader->messageLen + 1,
                                        sizeof(char)));
        if (!commHeader->dataToTransfer)
        {
            throw SERVER_EXCEPTION(SERVER_ALLOCATION_ERR);
        }

        strcpy(commHeader->dataToTransfer, screens->uiScreen.msg);
        commHeader->commType = UI_TRANSFER;
    }

    void ControlServer::getAndProcessUserInput() throw()
    {
        log->LOG("ControlServer::getAndProcessUserInput");

        if (-1 == read(sock_new, commHeader, sizeof(ClientServerComm) - sizeof(char*)))
        {
            log->LOG("ControlServer::getUserInput - Error reading header from socket");
            throw SERVER_EXCEPTION(SERVER_SOCKET_READ_ERR);
        }

        if (commHeader->dataToTransfer)
        {
            free(commHeader->dataToTransfer);
            commHeader->dataToTransfer = NULL;
        }
        commHeader->dataToTransfer = static_cast<char*>(calloc(commHeader->messageLen + 1,
                                        sizeof(char)));
        if (!commHeader->dataToTransfer)
        {
            log->LOG("ControlServer::getUserInput - Error allocating memory");
            throw SERVER_EXCEPTION(SERVER_ALLOCATION_ERR);
        }

        if (-1 == read(sock_new, commHeader->dataToTransfer, commHeader->messageLen))
        {
            log->LOG("ControlServer::getUserInput - Error reading header from socket");
            throw SERVER_EXCEPTION(SERVER_SOCKET_READ_ERR);
        }

        processUserInput(commHeader, &currentScreen, sock_new);

        sendDataToClient();
    }

    static void writeAll(char *buf, size_t bytesToWrite, int sockFd)
    {
        ssize_t bytesWrote = 0;
        while (bytesToWrite > 0)
        {
            cout << "ControlClient::readDataFromServer bytesToWrite is " << bytesToWrite << endl;
            bytesWrote = write(sockFd, buf, bytesToWrite);
            cout << "ControlClient::readDataFromServer bytes_read is " << bytesWrote << endl;
            if (-1 == bytesWrote)
            {
                cout << "ControlClient::readDataFromServer - Error reading string from socket" << endl;
                throw CLIENT_EXCEPTION(CLIENT_SOCKET_READ_ERR);
            }
            
            buf += bytesWrote;
            bytesToWrite -= bytesWrote;
        }
    }

	void ControlServer::sendDataToClient(ClientServerComm *commHeader) throw()
	{
        log->LOG("ControlServer::sendDataToClient");

        writeAll(reinterpret_cast<char*>(commHeader), 
                    sizeof(ClientServerComm) - sizeof(char*) + commHeader->messageLen, sock_new);
	}

    void ControlServer::sendDataToClient() throw()
	{
        log->LOG("ControlServer::sendDataToClient");

        sendDataToClient(commHeader);
	}

    void ControlServer::setData(const char *data)
    {
        if (commHeader->dataToTransfer)
        {
            free(commHeader->dataToTransfer);
            commHeader->dataToTransfer = NULL;
        }

        commHeader->dataToTransfer = static_cast<char*>(calloc(strlen(data), 
                                        sizeof(char)));
        if (!commHeader->dataToTransfer)
        {
            throw SERVER_EXCEPTION(SERVER_ALLOCATION_ERR);
        }
        strcpy(commHeader->dataToTransfer, data);
    }
}//namespace autoTrader