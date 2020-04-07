/**
 * control_client.cpp
 **/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
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
        return 0;
    }

    int ControlClient::sendUserInput(string userSelection)
    {
        return 0;
    }

    ClientServerUi ControlClient::getNewUi()
    {
        ClientServerUi ret = {"Please enter your selection...", INT};
        
        return ret;
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
            cin >> strUserChoice;
            res = client.sendUserInput(strUserChoice);
            
            if (res)
            {
                break;
            }
        }
    }

    if (res)
    {
        cout << "Quiting with error - " << res << endl;
    }

    return res;
}