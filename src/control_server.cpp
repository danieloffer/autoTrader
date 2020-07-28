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

        commHeader->commType = E_UI_TRANSFER;

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

        if (E_INT == screens[*currentScreen].uiScreen.expectedInput)
        {
            int intUserInput = atoi(commHeader->dataToTransfer);
            *currentScreen = screens[*currentScreen].actions[intUserInput](&intUserInput);
            if (4 == *currentScreen)
            {
                commHeader->commType = E_STOCK_DATA_TRANSFER;
            }
            else if (1 == *currentScreen)
            {
                commHeader->commType = E_BUY;
            }
            else if (2 == *currentScreen)
            {
                commHeader->commType = E_SELL;
            }

            if (commHeader->dataToTransfer)
            {
                free(commHeader->dataToTransfer);
                commHeader->dataToTransfer = NULL;
            }
            commHeader->messageLen = strlen(screens[*currentScreen].uiScreen.msg);
            commHeader->dataToTransfer = static_cast<char*>(calloc(commHeader->messageLen + 1,
                                            sizeof(char)));
            if (!commHeader->dataToTransfer)
            {
                throw SERVER_EXCEPTION(SERVER_ALLOCATION_ERR);
            }

            strcpy(commHeader->dataToTransfer, screens[*currentScreen].uiScreen.msg);
            commHeader->isMoreComm = 0;
        }
        else if(E_STR == screens[*currentScreen].uiScreen.expectedInput)
        {
            if (E_STOCK_DATA_TRANSFER == commHeader->commType)
            {
                *currentScreen = serverGetData(commHeader->dataToTransfer);
            }
            else if (E_BUY == commHeader->commType)
            {
                *currentScreen = buyStock(commHeader->dataToTransfer);
            }
            else if (E_SELL == commHeader->commType)
            {
                *currentScreen = sellStock(commHeader->dataToTransfer);
            }

            commHeader->isMoreComm = 0;

            if (commHeader->dataToTransfer)
            {
                free(commHeader->dataToTransfer);
                commHeader->dataToTransfer = NULL;
            }
            commHeader->messageLen = strlen(screens[*currentScreen].uiScreen.msg);
            commHeader->dataToTransfer = static_cast<char*>(calloc(commHeader->messageLen + 1,
                                            sizeof(char)));
            if (!commHeader->dataToTransfer)
            {
                throw SERVER_EXCEPTION(SERVER_ALLOCATION_ERR);
            }

            strcpy(commHeader->dataToTransfer, screens[*currentScreen].uiScreen.msg);
            commHeader->commType = E_UI_TRANSFER;
        }
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
    }

    static void writeAll(char *buf, size_t bytesToWrite, int sockFd)
    {
        ssize_t bytesWrote = 0;
        while (bytesToWrite > 0)
        {
            cout << "ControlServer::writeAll bytesToWrite is " << bytesToWrite << endl;
            bytesWrote = write(sockFd, buf, bytesToWrite);
            cout << "ControlServer::writeAll bytesWrote is " << bytesWrote << endl;
            if (-1 == bytesWrote)
            {
                cout << "ControlServer::writeAll - Error reading string from socket" << endl;
                throw CLIENT_EXCEPTION(CLIENT_SOCKET_READ_ERR);
            }
            
            buf += bytesWrote;
            bytesToWrite -= bytesWrote;
        }
    }

	void ControlServer::sendDataToClient(ClientServerComm *commHeader) throw()
	{
        char *tempBuf = reinterpret_cast<char*>(calloc(sizeof(ClientServerComm) - sizeof(char*) + commHeader->messageLen, sizeof(char)));
        log->LOG("ControlServer::sendDataToClient");

        if (!tempBuf)
        {
            throw SERVER_EXCEPTION(SERVER_ALLOCATION_ERR);
        }
        commHeader->serialize(tempBuf);
        writeAll(tempBuf, 
                    sizeof(ClientServerComm) - sizeof(char*) + commHeader->messageLen, sock_new);
        free(tempBuf);
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
        commHeader->messageLen = strlen(data);
    }

    void ControlServer::setIsMoreComm(int inIsMoreComm)
    {
        commHeader->isMoreComm = inIsMoreComm;
    }
}//namespace autoTrader