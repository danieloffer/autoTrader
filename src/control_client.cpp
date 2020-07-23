/**
 * control_client.cpp
 **/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <control_client.hpp>
#include <exception_types.hpp>

using namespace std;

namespace autoTrader
{
    ControlClient::ControlClient() throw()
    {
        struct sockaddr_in addr = {0};

        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd == -1)
        {
            perror("socket: ");
            throw CLIENT_EXCEPTION(CLIENT_CONNECTION_ERR);
        }

        socklen_t len = sizeof(addr);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(SERVER_PORT_NUM);
        addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

        if (-1 == connect(sock_fd, (struct sockaddr *)&addr, len))
        {
            cout << "Error connecting to " << SERVER_ADDR << " on port " << SERVER_PORT_NUM << endl;
            perror("connect: ");
            throw CLIENT_EXCEPTION(CLIENT_CONNECTION_ERR);
        }

        commHeader = static_cast<ClientServerComm*>(calloc(sizeof(ClientServerComm), sizeof(char)));
        if (!commHeader)
        {
            cout << "Error allocating memory" << endl;
        }
    }

    ControlClient::~ControlClient()
    {
        close(sock_fd);
        
        if (commHeader)
        {
            if (commHeader->dataToTransfer)
            {
                free(commHeader->dataToTransfer);
            }

            free(commHeader);
        }
    }

    static void handleData(ClientServerComm *commHeader)
    {
        cout << commHeader->dataToTransfer << endl;
    }

    static void readAll(char *buf, size_t bytesToRead, int sockFd)
    {
        ssize_t bytesRead = 0;
        while (bytesToRead > 0)
        {
            cout << "ControlClient::readDataFromServer bytesToRead is " << bytesToRead << endl;
            bytesRead = read(sockFd, buf, bytesToRead);
            cout << "ControlClient::readDataFromServer bytes_read is " << bytesRead << endl;
            if (-1 == bytesRead)
            {
                cout << "ControlClient::readDataFromServer - Error reading string from socket" << endl;
                throw CLIENT_EXCEPTION(CLIENT_SOCKET_READ_ERR);
            }
            
            buf += bytesRead;
            bytesToRead -= bytesRead;
        }
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

    void ControlClient::recvAndHandleDataFromServer() throw()
    {
        if (-1 == read(sock_fd, commHeader, 
                    (sizeof(ClientServerComm) - sizeof(char*))))
        {
            cout << "ControlClient::recvAndHandleDataFromServer - Error reading header from socket" << endl;
            throw CLIENT_EXCEPTION(CLIENT_SOCKET_READ_ERR);
        }

        if (commHeader->dataToTransfer)
        {
            free(commHeader->dataToTransfer);
            commHeader->dataToTransfer = NULL;
        }
        commHeader->dataToTransfer = static_cast<char*>(calloc(commHeader->messageLen + 1, sizeof(char)));
        if (!commHeader->dataToTransfer)
        {
            cout << "ControlClient::recvAndHandleDataFromServer - Error allocating buffer" << endl; 
            throw CLIENT_EXCEPTION(CLIENT_ALLOCATION_ERR);
        }

        readAll(commHeader->dataToTransfer, commHeader->messageLen, sock_fd);

        handleData(commHeader);
        
        if (commHeader->dataToTransfer)
        {
            free(commHeader->dataToTransfer);
            commHeader->dataToTransfer = NULL;
        }
    }

    int ControlClient::getAndsendUserDataToServer() throw()
    {
        string userChoice;
        int res = 1;

        cout << "ControlClient::getAndsendUserDataToServer" <<  endl;

        cin >> userChoice;
        if (commHeader->dataToTransfer)
        {
            free(commHeader->dataToTransfer);
            commHeader->dataToTransfer = NULL;
        }
        commHeader->dataToTransfer = static_cast<char*>(calloc(userChoice.length() + 1,
                                        sizeof(char)));
        if (!commHeader->dataToTransfer)
        {
            cout << "Error allocating memory for stock data" << endl;
            res = 0;
        }

        strcpy(commHeader->dataToTransfer, userChoice.c_str());
        commHeader->messageLen = strlen(commHeader->dataToTransfer);

        writeAll(reinterpret_cast<char*>(commHeader), 
                    sizeof(ClientServerComm) - sizeof(char*) + commHeader->messageLen, sock_fd);

        if (commHeader->dataToTransfer)
        {
            free(commHeader->dataToTransfer);
            commHeader->dataToTransfer = NULL;
        }

        return res;
    }
}//namespace autoTrader

using namespace autoTrader;
    
int main(int argc, char *argv[])
{
    ControlClient client = ControlClient();
    int res = 0;

    cout << "Welcome to autoTrader's remote control program" << endl;

    while (1)
    {
        try
        {
            client.recvAndHandleDataFromServer();
            client.getAndsendUserDataToServer();
        }
        catch(ClientError& e)
        {
            cout << "Caught an exception, sleeping for 1 sec and try again" << endl;
            std::cerr << e.what() << "at:" << e.getFileName() << ":" << e.getFuncName() << ":" << e.getLine() << endl;
        }
        
    }

    if (res)
    {
        cout << "Quiting with error - " << res << endl;
    }

    return res;
}