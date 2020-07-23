/*
* unit_test_control_server.cpp
*/

#include <server.hpp>
#include <exception_types.hpp>
#include <iostream>
#include <unistd.h>

using namespace autoTrader;
using namespace std;

int main()
{
	ControlServer *server = NULL;
	try
	{
		server = Server::getInstance();
	}
	catch(const std::exception& e)
	{
		cout << "Sleeping for 3 seconds to allow the socket to be available" << endl;
		sleep(3);
	}

	while(1)
	{
		try
		{
			server->sendDataToClient();

			server->getAndProcessUserInput();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			sleep(1);
		}	
	}
	
	

	return 0;
}