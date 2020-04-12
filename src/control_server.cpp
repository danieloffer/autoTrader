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

using namespace std;

namespace autoTrader
{
    ControlServer::ControlServer() : log(Logger::getInstance()), currentScreen(0)
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

        if (-1 == write(sock_new, &screens[currentScreen].uiScreen.expectedInputType, 
			sizeof(screens[currentScreen].uiScreen.expectedInputType)))
        {
            log->LOG("ControlServer::presentUi - Error writing to socket");
        }
        if (-1 == write(sock_new, screens[currentScreen].uiScreen.uiMessage, 
						strlen(screens[currentScreen].uiScreen.uiMessage) + 1))
        {
            log->LOG("ControlServer::presentUi - Error writing to socket");
        }
    }

    void ControlServer::processUserInput()
    {
        size_t bytesToRead = 0;

        log->LOG("ControlServer::getUserInput");

        if (INT == screens[currentScreen].uiScreen.expectedInputType)
        {
            int userInputInt = 0;

            bytesToRead = sizeof(int);

            if (-1 == read(sock_new, &userInputInt, bytesToRead))
            {
                log->LOG("ControlServer::getUserInput - Error reading from socket");
            }

            log->LOG("ControlServer::getUserInput - user pressed: " + to_string(userInputInt));

			if (!userInputInt)
			{
				cout << "bye bye" << endl;
                exit(1);
			}
			else
			{
				currentScreen = screens[currentScreen].actions[userInputInt](&userInputInt);
			}
        }
        else
        {
            bytesToRead = MAX_MSG_LEN;
            void *userInput = calloc(bytesToRead, sizeof(char));

            if (!userInput)
            {
                log->LOG("ControlServer::getUserInput - Error allocation buffer");
            }
            if (-1 == read(sock_new, userInput, bytesToRead))
            {
                log->LOG("ControlServer::getUserInput - Error reading from socket");
            }

			log->LOG("ControlServer::getUserInput - user entered: " + string((char*)userInput));

			currentScreen = screens[currentScreen].actions[0](userInput);
        	
			free(userInput);
			userInput = NULL;
        }
    }

	void ControlServer::sendDataToClient(void *data)
	{
		int bytes_written;
		char *dataToSend = (char*)data;
		size_t count = strlen(dataToSend) + 1;

        log->LOG("ControlServer::sendDataToClient - sending data to client");

        write(sock_new, &count, sizeof(count));

		while (count > 0)
		{
			bytes_written = write(sock_new, dataToSend, count);
			
			dataToSend += bytes_written;
			count -= bytes_written;
		}

        log->LOG("ControlServer::sendDataToClient - completed sending data to client");
	}
}//namespace autoTrader