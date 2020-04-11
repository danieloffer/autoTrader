/*
* unit_test_control_server.cpp
*/

#include <control_server.hpp>

using namespace autoTrader;
using namespace std;

int main()
{
	ControlServer *server = getInstance();

	while(1)
	{
		server->presentUi();

		server->processUserInput();
	}

	return 0;
}