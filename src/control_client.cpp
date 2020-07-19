/**
 * control_client.cpp
 **/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <control_client.hpp>

using namespace std;

namespace autoTrader
{
    ControlClient::ControlClient()
    {
        struct sockaddr_in addr = {0};

        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd == -1)
        {
            perror("socket: ");
        }

        socklen_t len = sizeof(addr);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(SERVER_PORT_NUM);
        addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

        if (-1 == connect(sock_fd, (struct sockaddr *)&addr, len))
        {
            cout << "Error connecting to " << SERVER_ADDR << " on port " << SERVER_PORT_NUM << endl;
            perror("connect: ");
        }
    }
    ControlClient::~ControlClient()
    {
        close(sock_fd);
    }

    int ControlClient::sendUserInput(int userSelection)
    {
        if (-1 == write(sock_fd, &userSelection, sizeof(int)))
        {
            cout << "ControlClient::sendUserInput(int) - Error writing to socket" << endl;
        }

        return 0;
    }

    int ControlClient::sendUserInput(string userSelection)
    {
        if (-1 == write(sock_fd, userSelection.c_str(), userSelection.length() + 1))
        {
            cout << "ControlClient::sendUserInput(string) - Error writing to socket" << endl;

            return 1;
        }

        return 0;
    }

    ClientServerUi ControlClient::getNewUi()
    {
        ClientServerUi ret = {NULL};
        void *buf = NULL;
        int expectedInputType = 0;
        ssize_t msgSize = 0;

        buf = calloc(MAX_MSG_LEN, sizeof(char));
        if (!buf)
        {
            cout << "ControlClient::getNewUi - Error allocating buffer" << endl;

            return ret;
        }
        
        if (-1 == read(sock_fd, &expectedInputType, sizeof(int)))
        {
            cout << "ControlClient::getNewUi - Error reading from socket" << endl;
        }
        ret.expectedInputType = (E_InputType)expectedInputType;

        msgSize = read(sock_fd, buf, MAX_MSG_LEN);
        if (-1 == msgSize)
        {
            cout << "ControlClient::getNewUi - Error reading from socket" << endl;
        }
        ret.uiMessage = (char *)calloc(msgSize, sizeof(char));
        if (!ret.uiMessage)
        {
            cout << "ControlClient::getNewUi - Error allocating buffer" << endl; 
        }
        memmove(ret.uiMessage, buf, msgSize);


        free(buf);
        
        return ret;
    }

    void ControlClient::readDataFromServer(char *buf)
    {
        int bytes_read = 0;
        size_t count = MAX_DATA_LEN; 

        read(sock_fd, &count, sizeof(count));

        while (count > 0)
        {
            bytes_read = read(sock_fd, buf, count);
            
            buf += bytes_read;
            count -= bytes_read;
        }
    }
}//namespace autoTrader

using namespace autoTrader;
    
int main(int argc, char *argv[])
{
    ControlClient client = ControlClient();
    int userChoice = 0;
    string strUserChoice;
    ClientServerUi currentUiScreen;
    int res = 0;

    cout << "Welcome to autoTrader's remote control program" << endl;

    while (1)
    {
        currentUiScreen = client.getNewUi();
        cout << currentUiScreen.uiMessage << endl;
        free(currentUiScreen.uiMessage);

        if (currentUiScreen.expectedInputType == INT)
        {
            cin >> userChoice;
            if (!userChoice)
            {
                cout << "Quiting control client..." << endl;
                break;
            }

            res = client.sendUserInput(userChoice);
            
            if (res)
            {
                break;
            }
        }
        else if (currentUiScreen.expectedInputType == STR)
        {
            char *buf = NULL;

            cin >> strUserChoice;
            res = client.sendUserInput(strUserChoice);
            
            if (res)
            {
                break;
            }

            buf = (char*)calloc(MAX_DATA_LEN, sizeof(char));
            if (!buf)
            {
                cout << "Error allocating memory for stock data" << endl;
                break;
            }

            client.readDataFromServer(buf);
            cout << "Got data from server. Printing to screen" << endl;
            cout << buf << endl;
        }
    }

    if (res)
    {
        cout << "Quiting with error - " << res << endl;
    }

    return res;
}