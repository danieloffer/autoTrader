/**
 * server_operations.cpp
 **/

#include <iostream>
#include <server.hpp>
#include <data_scraper.hpp>

using namespace std;

namespace autoTrader
{
	int actionBuy(void *param)
	{
		cout << "going to buy screen" << endl;

		return 1;
	}

	int actionSell(void *param)
	{
		cout << "going to sell screen" << endl;

		return 2;
	}

	int actionSettings(void *param)
	{
		cout << "going to settings screen" << endl;

		return 3;
	}

    int actiongetData(void *param)
    {
        cout << "going to get data screen" << endl;

        return 4;
    }

	int actionVoid(void *param)
	{
		cout << "invalid input" << endl;

		return 0;
	}

	int buyStock(void *param)
	{
		cout << "bought stock" << endl;

		return 0;
	}

	int sellStock(void *param)
	{
		cout << "sold stock" << endl;

		return 0;
	}

	int getLogs(void *param)
	{
		cout << "sent logs" << endl;

		return 0;
	}

	int setInterval(void *param)
	{
		cout << "Interval was set" << endl;

		return 0;
	}

    int serverGetData(void *param)
    {
        cout << "Getting data for " << (char*)param << "..." << endl;
        DataScraper scraper;
		ControlServer *server = Server::getInstance();
        string data = scraper.getStockData(string((char*)param), DataScraper::DAILY_ADJ);

        server->sendDataToClient((void*)(data.c_str()));

        cout << "sent data to client" << endl;

        return 0;
    }
}//namespace autoTrader
