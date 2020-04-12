/*
* unit_test_control_server.cpp
*/

#include <server.hpp>

using namespace autoTrader;
using namespace std;

int main()
{
	ControlServer *server = Server::getInstance();

	while(1)
	{
		server->presentUi();

		server->processUserInput();
	}

	return 0;
}